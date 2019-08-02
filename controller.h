#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector3D>
#include <QQuaternion>
#include <QImage>

#include "customtype.h"

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool lost READ lost WRITE setLost NOTIFY lostChanged)

    Q_PROPERTY(QVector3D cameraPose READ cameraPose WRITE setCameraPose NOTIFY cameraPoseChanged)
    Q_PROPERTY(QQuaternion cameraOrientation READ cameraOrientation WRITE setCameraOrientation NOTIFY cameraOrientationChanged)

    Q_PROPERTY(QVector<QVector3D> arPlan READ arPlan WRITE setArPlan NOTIFY arPlanChanged)
    Q_PROPERTY(QVector3D arCenter READ arCenter WRITE setArCenter NOTIFY arCenterChanged)
    Q_PROPERTY(bool arReady READ arReady WRITE setArReady NOTIFY arReadyChanged)

    Q_PROPERTY(Surface surface READ surface WRITE setSurface NOTIFY surfaceChanged)
    Q_PROPERTY(Surface currentSurface READ currentSurface WRITE setCurrentSurface NOTIFY currentSurfaceChanged)

    Q_PROPERTY(QVector<QVector3D> voxels READ voxels WRITE setVoxels NOTIFY voxelsChanged)
    Q_PROPERTY(double voxelSize READ voxelSize WRITE setVoxelSize NOTIFY voxelSizeChanged)
    Q_PROPERTY(int voxelsCount READ voxelsCount WRITE setVoxelsCount NOTIFY voxelsCountChanged)

    QVector3D m_cameraPose;
    QQuaternion m_cameraOrientation;

    QVector<QVector3D> m_arPlan;
    QVector3D m_arCenter;
    bool m_arReady = false;

    bool m_lost = true;

    Surface m_surface;
    Surface m_currentSurface;

    QVector<QVector3D> m_voxels;

    double m_voxelSize = 0.0;
    int m_voxelsCount = 0;

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();

    QVector3D cameraPose() const;
    QQuaternion cameraOrientation() const;

    void setFrames(const QByteArray &left, const QByteArray &right , int width, int height);

    QByteArray leftImage;
    QByteArray rightImage;
    int width = 0;
    int height = 0;

    Q_INVOKABLE QVector3D getVoxel( int i ) const {
        if( i >= 0 && i < m_voxels.size() ){
            return m_voxels.at(i);
        }else{
            return QVector3D();
        }
    }
    Q_INVOKABLE int getArPlaneSize() const {
        return m_arPlan.size();
    }
    Q_INVOKABLE QVector3D getArPlane( int i ) const {
        if( i >= 0 && i < m_arPlan.size() ){
            return m_arPlan.at(i);
        }else{
            return QVector3D();
        }
    }

    QVector<QVector3D> arPlan() const;
    QVector3D arCenter() const;
    bool arReady() const;

    bool lost() const;

    Surface surface() const
    {
        return m_surface;
    }

    Surface currentSurface() const
    {
        return m_currentSurface;
    }

    QVector<QVector3D> voxels() const
    {
        return m_voxels;
    }

    double voxelSize() const
    {
        return m_voxelSize;
    }

    int voxelsCount() const
    {
        return m_voxelsCount;
    }

signals:
    void cameraPoseChanged( QVector3D cameraPose );
    void cameraOrientationChanged(QQuaternion cameraOrientation);

    void newLeftImage( QImage image );
    void newLeftImagePtr( QSharedPointer<QByteArray> ptr );

    void arPlanChanged(QVector<QVector3D> arPlan);
    void arCenterChanged(QVector3D arCenter);
    void arReadyChanged(bool arReady);

    void lostChanged(bool lost);

    void surfaceChanged(Surface surface);

    void currentSurfaceChanged(Surface currentSurface);

    void voxelsChanged(QVector<QVector3D> voxels);


    void voxelSizeChanged(double voxelSize);

    void voxelsCountChanged(int voxelsCount);

public slots:
    void setCameraPose( QVector3D cameraPose );
    void setCameraOrientation(QQuaternion cameraOrientation);

    void setPlane(int index, QVector<QVector3D> points, QVector3D n);

    void setArPlan(QVector<QVector3D> arPlan);
    void setArCenter(QVector3D arCenter);
    void setArReady(bool arReady);

    bool cameraAvailable();
    void start();

    void reset();

    void setLost(bool lost);
    void setSurface(Surface surface)
    {
        m_surface = surface;
        emit surfaceChanged(m_surface);
    }
    void setCurrentSurface(Surface currentSurface)
    {
        m_currentSurface = currentSurface;
        emit currentSurfaceChanged(m_currentSurface);
    }

    void setVoxels(QVector<QVector3D> voxels)
    {
        if (m_voxels == voxels)
            return;

        qDebug() << voxels.size();

        //setVoxelsCount( 0 );
        m_voxels = voxels;
        emit voxelsChanged(m_voxels);
        setVoxelsCount( m_voxels.size() );
    }
    void setVoxelSize(double voxelSize)
    {
        if (qFuzzyCompare(m_voxelSize, voxelSize))
            return;

        m_voxelSize = voxelSize;
        emit voxelSizeChanged(m_voxelSize);
    }
    void setVoxelsCount(int voxelsCount)
    {
        if (m_voxelsCount == voxelsCount)
            return;

        m_voxelsCount = voxelsCount;
        emit voxelsCountChanged(m_voxelsCount);
    }
};

#endif // CONTROLLER_H
