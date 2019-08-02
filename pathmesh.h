#ifndef PATHMESH_H
#define PATHMESH_H

#include <QGeometryRenderer>
#include <QVector3D>
#include <Qt3DRender>
#include <QVector>

class PathMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(QVector<QVector3D> path READ path WRITE setPath NOTIFY pathChanged)


public:
    explicit PathMesh(Qt3DCore::QNode *parent = nullptr);

    QVector<QVector3D> path() const;

private:
    QVector<QVector3D> m_path;
    Qt3DRender::QBuffer *m_buf = Q_NULLPTR;
    Qt3DRender::QAttribute *m_positionAttibute = Q_NULLPTR;

signals:
    void pathChanged(QVector<QVector3D> path);

public slots:
    void setPath(const QVector<QVector3D> &path);
    void push( const QVector3D &point );
    void clear();
};

#endif // PATHMESH_H
