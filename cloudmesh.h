#ifndef CLOUDMESH_H
#define CLOUDMESH_H
#include <QGeometryRenderer>
#include <QVector3D>
#include <Qt3DRender>
#include <QVector>

class CloudMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(QVector<QVector3D> cloud READ cloud WRITE setCloud NOTIFY cloudChanged)

public:
    explicit CloudMesh(Qt3DCore::QNode *parent = nullptr);

    QVector<QVector3D> cloud() const;

private:
    QVector<QVector3D> m_cloud;
    Qt3DRender::QBuffer *m_buf = Q_NULLPTR;
    Qt3DRender::QAttribute *m_positionAttibute = Q_NULLPTR;

signals:
    void cloudChanged(QVector<QVector3D> cloud);

public slots:
    void setCloud(QVector<QVector3D> cloud);
    void push( const QVector3D &point );
    void clear();
};

#endif // CLOUDMESH_H
