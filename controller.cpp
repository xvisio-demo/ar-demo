#include <cmath>
#include "controller.h"

#include <deque>

#include <xslam/xslam_sdk.hpp>

void xslam_ar_plane_stereo_ready_callback(std::function<void()> f);
void xslam_ar_plane_tof_ready_callback(std::function<void()> f);

#include <QDebug>
#include <iostream>

#include <Eigen/Core>
using Rotation = Eigen::Matrix3d;
using Translation = Eigen::Vector3d;

namespace
{

struct Pose
{
    Rotation rotation_;
    Translation translation_;

    Pose():rotation_(Rotation::Identity()), translation_{0,0,0} {}

    Translation& translation() { return translation_; }
    Rotation& rotation() { return rotation_; }

    Pose& rotation(const Rotation& rot) { rotation_ = rot; return *this; }
    Pose& translation(const Translation& trans) { translation_ = trans; return *this; }
};

Pose xslam_to_core(xslam_pose const& xrt)
{
    Pose rt;
    rt.rotation() = Eigen::Map<Eigen::Matrix<float,3,3> const>(xrt.rotation).transpose().cast<double>();
    rt.translation() << static_cast<double>(xrt.x), static_cast<double>(xrt.y), static_cast<double>(xrt.z);
    return rt;
}

}




Controller::Controller(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QSharedPointer<QByteArray>>("QSharedPointer<QByteArray>");
    qRegisterMetaType<QVector<QPointF>>("QVector<QPointF>");
    qRegisterMetaType<Surface>("Surface");
    qRegisterMetaType<Voxels>("Voxels");

    xslam_6dof_callback( static_cast<std::function<void (xslam_pose*)>>([this]( xslam_pose *pose ){

        Pose xPose = xslam_to_core( *pose );
        Pose ca;
        ca.rotation() << -1,0,0,
        0,-1,0,
        0,0,1;
        ca.translation() << 0.04,0,0;
        Pose poseCam =  Pose().rotation(xPose.rotation() *ca.rotation()).translation((xPose.rotation() * ca.translation()) + xPose.translation());

#if 0
        // IMU position
        QVector3D position( -pose-x, -pose-y, pose-z );
#else
        // Camera position
        QVector3D position( static_cast<float>(-poseCam.translation().x()), static_cast<float>(-poseCam.translation().y()), static_cast<float>(poseCam.translation().z()) );
#endif

#if 0
        QMatrix3x3 m;
        for(int i=0; i<9; i++){
        m.data()[i] = poseCam.rotation()(i);
        }
        QQuaternion orientation = QQuaternion::fromRotationMatrix( m.transposed() );
#else
        QQuaternion orientation = QQuaternion::fromEulerAngles( -pose->pitch, -pose->yaw, pose->roll );
#endif

        setCameraPose( position );
        setCameraOrientation( orientation );

        setLost( false );
    }));

    xslam_lost_callback( static_cast<std::function<void (float)>>([this](float){
        setLost( true );
    }));


    xslam_frame_callback( static_cast<std::function<void (xslam_frame*)>>([this]( xslam_frame *frame ){
        QByteArray left;
        left.resize( frame->width * frame->height );
        memcpy(left.data(), frame->left, static_cast<size_t>(left.size()));
        QByteArray right;
        right.resize( frame->width * frame->height );
        memcpy(right.data(), frame->right, static_cast<size_t>(right.size()));
        setFrames( left, right, frame->width, frame->height );
    }));


    xslam_planes_tof_callback( static_cast<std::function<void (xslam_plane*, int)>>([this](xslam_plane *planes, int size){
        for(int i = 0 ; i < size ; ++i){
            QVector3D n( planes[i].n[0] , planes[i].n[1] , planes[i].n[2] );
            QVector<QVector3D> pts;
            for(int p = 0 ; p < planes[i].border_size ; ++p){
                pts << QVector3D( -planes[i].border[p].x, -planes[i].border[p].y, planes[i].border[p].z);
            }
            this->setPlane( i, pts, n);
        }
    }));

    xslam_ar_plane_stereo_ready_callback( static_cast<std::function<void ()>>([this](){
        setArReady( true );
    }) );
}

Controller::~Controller()
{

}

QVector3D Controller::cameraPose() const
{
    return m_cameraPose;
}

QQuaternion Controller::cameraOrientation() const
{
    return m_cameraOrientation;
}

void Controller::setFrames(const QByteArray &left, const QByteArray &right, int width, int height)
{
    QImage leftI(reinterpret_cast<const unsigned char*>(left.data()), width, height, QImage::Format_Grayscale8);
    leftI = leftI.copy();
    emit newLeftImage( leftI );

    this->width = width;
    this->height = height;
    this->leftImage = left;
    this->rightImage = right;

    QSharedPointer<QByteArray> dleft = QSharedPointer<QByteArray>(new QByteArray);
    *dleft.data() = left;
    emit newLeftImagePtr( dleft );
    //QSharedPointer<QByteArray> dright = QSharedPointer<QByteArray>(new QByteArray);
    //emit newRightImage( dright );
}

QVector<QVector3D> Controller::arPlan() const
{
    return m_arPlan;
}

QVector3D Controller::arCenter() const
{
    return m_arCenter;
}

bool Controller::arReady() const
{
    return m_arReady;
}

bool Controller::lost() const
{
    return m_lost;
}

void Controller::setCameraPose(QVector3D cameraPose)
{
    if (m_cameraPose == cameraPose)
        return;
    m_cameraPose = cameraPose;
    emit cameraPoseChanged(m_cameraPose);
}

void Controller::setCameraOrientation(QQuaternion cameraOrientation)
{
    if (m_cameraOrientation == cameraOrientation)
        return;

    m_cameraOrientation = cameraOrientation;
    emit cameraOrientationChanged(m_cameraOrientation);
}

void Controller::setPlane(int index, QVector<QVector3D> points, QVector3D n)
{
    Q_UNUSED( index )

    if( m_arReady )
        return;

    if( points.empty() )
        return;

    auto res = QVector3D::dotProduct( QVector3D(0,1,0), n.normalized() );
    res = fabsf( res );

    if( res > 0.8f ){
        if( !arReady() ){
            setArPlan( points );
            QVector3D c;
            foreach( const QVector3D &p, points){
                c += p;
            }
            c /= points.size();
            setArCenter( c );
        }
    }
}

void Controller::setArPlan(QVector<QVector3D> arPlan)
{
    if (m_arPlan == arPlan)
        return;

    m_arPlan = arPlan;
    emit arPlanChanged(m_arPlan);
}

void Controller::setArCenter(QVector3D arCenter)
{
    if (m_arCenter == arCenter)
        return;

    m_arCenter = arCenter;
    emit arCenterChanged(m_arCenter);
}

void Controller::setArReady(bool arReady)
{
    qDebug() << "Plane ready = " << arReady;

    if (m_arReady == arReady)
        return;

    m_arReady = arReady;
    emit arReadyChanged(m_arReady);
}

bool Controller::cameraAvailable()
{
    return xslam_camera_is_detected() > 0;
}

void Controller::start()
{
    xslam_start_vo();
}

void Controller::reset()
{
    xslam_stop();
    setLost( true );
    setArReady( false );
    setArPlan( QVector<QVector3D>() );
    setArCenter( QVector3D() );

    start();
}

void Controller::setLost(bool lost)
{
    if (m_lost == lost)
        return;

    m_lost = lost;
    emit lostChanged(m_lost);
}
