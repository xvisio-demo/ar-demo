#include "pointmesh.h"

PointMesh::PointMesh(Qt3DCore::QNode *parent) : QGeometryRenderer(parent)
{
    auto *geometry = new Qt3DRender::QGeometry(this);

    QByteArray bufferBytes;
    bufferBytes.resize(3 * sizeof(float));
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = m_point.x();
    *positions++ = m_point.y();
    *positions++ = m_point.z();

    m_buf = new Qt3DRender::QBuffer(geometry);
    m_buf->setData(bufferBytes);

    auto *positionAttribute = new Qt3DRender::QAttribute(geometry);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(m_buf);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(1);
    geometry->addAttribute(positionAttribute);

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
    this->setGeometry( geometry );
}

QVector3D PointMesh::point() const
{
    return m_point;
}

void PointMesh::setPoint(QVector3D point)
{
    if (m_point == point)
        return;

    m_point = point;

    QByteArray bufferBytes;
    bufferBytes.resize(3 * sizeof(float));
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = m_point.x();
    *positions++ = m_point.y();
    *positions++ = m_point.z();

    if( m_buf )
        m_buf->updateData( 0, bufferBytes );

    emit pointChanged(m_point);
}
