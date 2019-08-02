#ifndef CAMERAMESH_H
#define CAMERAMESH_H

#include <QGeometryRenderer>
#include <Qt3DRender>


class CameraMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(float depth READ depth WRITE setDepth NOTIFY depthChanged)

public:
    explicit CameraMesh(Qt3DCore::QNode *parent = nullptr);

    float width() const;
    float height() const;
    float depth() const;

protected:
    void updateVertices();

private:
    float m_width = 0.2f;
    float m_height = 0.15f;
    float m_depth = 0.15f;

    Qt3DRender::QAttribute *m_positionAttribute = Q_NULLPTR;
    Qt3DRender::QAttribute *m_indexAttribute = Q_NULLPTR;
    Qt3DRender::QBuffer *m_vertexBuffer = Q_NULLPTR;
    Qt3DRender::QBuffer *m_indexBuffer = Q_NULLPTR;

signals:
    void widthChanged(float width);
    void heightChanged(float height);
    void depthChanged(float depth);

public slots:
    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
};

#endif // CAMERAMESH_H
