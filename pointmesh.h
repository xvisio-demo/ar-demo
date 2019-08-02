#ifndef POINTMESH_H
#define POINTMESH_H

#include <QGeometryRenderer>
#include <QVector3D>
#include <Qt3DRender>

class PointMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(QVector3D point READ point WRITE setPoint NOTIFY pointChanged)

public:
    explicit PointMesh(Qt3DCore::QNode *parent = nullptr);

    QVector3D point() const;

private:
    QVector3D m_point;
    Qt3DRender::QBuffer *m_buf = Q_NULLPTR;

signals:
    void pointChanged(QVector3D point);

public slots:
    void setPoint(QVector3D point);
};

#endif // POINTMESH_H
