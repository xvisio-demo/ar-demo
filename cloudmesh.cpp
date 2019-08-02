#include "cloudmesh.h"


CloudMesh::CloudMesh(Qt3DCore::QNode *parent) : Qt3DRender::QGeometryRenderer(parent)
{
    auto *geometry = new Qt3DRender::QGeometry(this);

    QByteArray bufferBytes;
    bufferBytes.resize(static_cast<unsigned long>(m_cloud.size()) * 3 * sizeof(float) );
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    for(int i=0; i<m_cloud.size(); i++){
        *positions++ = m_cloud.at(i).x();
        *positions++ = m_cloud.at(i).y();
        *positions++ = m_cloud.at(i).z();
    }

    m_buf = new Qt3DRender::QBuffer(geometry);
    m_buf->setData(bufferBytes);

    m_positionAttibute = new Qt3DRender::QAttribute(geometry);
    m_positionAttibute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    m_positionAttibute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_positionAttibute->setVertexSize(3);
    m_positionAttibute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_positionAttibute->setBuffer(m_buf);
    m_positionAttibute->setByteStride(3 * sizeof(float));
    m_positionAttibute->setCount(m_cloud.size());
    geometry->addAttribute(m_positionAttibute);

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
    this->setGeometry( geometry );
}

QVector<QVector3D> CloudMesh::cloud() const
{
    return m_cloud;
}

void CloudMesh::setCloud(QVector<QVector3D> cloud)
{
    if (m_cloud == cloud)
        return;

    m_cloud = cloud;

    QByteArray bufferBytes;
    bufferBytes.resize(static_cast<unsigned long>(m_cloud.size()) * 3 * sizeof(float) );
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    for(int i=0; i<m_cloud.size(); i++){
        *positions++ = m_cloud.at(i).x();
        *positions++ = m_cloud.at(i).y();
        *positions++ = m_cloud.at(i).z();
    }

    m_buf->setData(bufferBytes);
    m_positionAttibute->setCount( m_cloud.size() );

    emit cloudChanged(m_cloud);
}

void CloudMesh::push(const QVector3D &point)
{
    auto p = cloud();
    p.push_back( point );
    setCloud( p );
}

void CloudMesh::clear()
{
    setCloud( QVector<QVector3D>() );
}
