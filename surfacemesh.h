#ifndef SURFACEMESH_H
#define SURFACEMESH_H

#include <QGeometryRenderer>
#include <QSize>
#include <Qt3DRender>

#include "customtype.h"

class SurfaceMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(Surface surface READ surface WRITE setSurface NOTIFY surfaceChanged)

public:
    explicit SurfaceMesh(Qt3DCore::QNode  *parent = nullptr);

    Surface surface() const;

protected:
    void updateVertices();
    void updateIndices();

private:
    Qt3DRender::QAttribute *m_positionAttribute = Q_NULLPTR;
    Qt3DRender::QAttribute *m_indexAttribute = Q_NULLPTR;
    Qt3DRender::QAttribute *m_normalAttribute = Q_NULLPTR;
    Qt3DRender::QBuffer *m_vertexBuffer = Q_NULLPTR;
    Qt3DRender::QBuffer *m_indexBuffer = Q_NULLPTR;

    Surface m_surface;

signals:
    void surfaceChanged(Surface surface);

public slots:
    void setSurface(Surface surface);
};

#endif // SURFACEMESH_H
