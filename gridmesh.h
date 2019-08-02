#ifndef GRIDMESH_H
#define GRIDMESH_H

#include <QGeometryRenderer>
#include <QSize>
#include <Qt3DRender>

class GridMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QSize resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)

public:
    explicit GridMesh(Qt3DCore::QNode  *parent = nullptr);

    float width() const;
    float height() const;
    QSize resolution() const;

protected:
    void updateVertices();    
    void updateIndices();

private:
    float m_width = 1.0f;
    float m_height = 1.0f;
    QSize m_resolution = QSize(10,10);

    Qt3DRender::QAttribute *m_positionAttribute = Q_NULLPTR;
    Qt3DRender::QAttribute *m_indexAttribute = Q_NULLPTR;
    Qt3DRender::QBuffer *m_vertexBuffer = Q_NULLPTR;
    Qt3DRender::QBuffer *m_indexBuffer = Q_NULLPTR;

signals:
    void widthChanged(float width);
    void heightChanged(float height);
    void resolutionChanged(QSize resolution);

public slots:
    void setWidth(float width);
    void setHeight(float height);
    void setResolution(QSize resolution);
};

#endif // GRIDMESH_H
