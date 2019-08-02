#include "linemesh.h"

LineMesh::LineMesh(Qt3DCore::QNode *parent) : QGeometryRenderer(parent)
{
    auto *geometry = new Qt3DRender::QGeometry(this);

    // position vertices (start and end)
    QByteArray bufferBytes;
    bufferBytes.resize(3 * 2 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = m_from.x();
    *positions++ = m_from.y();
    *positions++ = m_from.z();
    *positions++ = m_to.x();
    *positions++ = m_to.y();
    *positions++ = m_to.z();

    m_buf = new Qt3DRender::QBuffer(geometry);
    m_buf->setData(bufferBytes);

    auto *positionAttribute = new Qt3DRender::QAttribute(geometry);
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(m_buf);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(2);
    geometry->addAttribute(positionAttribute); // We add the vertices in the geometry

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    this->setGeometry( geometry );

}

QVector3D LineMesh::from() const
{
    return m_from;
}

QVector3D LineMesh::to() const
{
    return m_to;
}

float LineMesh::thickness() const
{
    return m_thickness;
}

void LineMesh::setFrom(QVector3D from)
{
    if (m_from == from)
        return;

    m_from = from;

    QByteArray bufferBytes;
    bufferBytes.resize(3 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = m_from.x();
    *positions++ = m_from.y();
    *positions++ = m_from.z();

    if( m_buf )
        m_buf->updateData( 0, bufferBytes );

    emit fromChanged(m_from);
}

void LineMesh::setTo(QVector3D to)
{
    if (m_to == to)
        return;

    m_to = to;

    QByteArray bufferBytes;
    bufferBytes.resize(3 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    *positions++ = m_to.x();
    *positions++ = m_to.y();
    *positions++ = m_to.z();

    if( m_buf )
        m_buf->updateData( 3*sizeof(float), bufferBytes );

    emit toChanged(m_to);
}

void LineMesh::setThickness(float thickness)
{
    if (qFuzzyCompare(m_thickness, thickness))
        return;

    m_thickness = thickness;
    emit thicknessChanged(m_thickness);
}
