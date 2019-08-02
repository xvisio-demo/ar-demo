#include "pathmesh.h"

PathMesh::PathMesh(Qt3DCore::QNode *parent) : Qt3DRender::QGeometryRenderer(parent)
{
    auto *geometry = new Qt3DRender::QGeometry(this);

    QByteArray bufferBytes;
    bufferBytes.resize(static_cast<unsigned long>(m_path.size()) * 3 * sizeof(float) );
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    for(int i=0; i<m_path.size(); i++){
        *positions++ = m_path.at(i).x();
        *positions++ = m_path.at(i).y();
        *positions++ = m_path.at(i).z();
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
    m_positionAttibute->setCount(m_path.size());
    geometry->addAttribute(m_positionAttibute);

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineStrip);
    this->setGeometry( geometry );
}

QVector<QVector3D> PathMesh::path() const
{
    return m_path;
}

void PathMesh::setPath(const QVector<QVector3D> &path)
{
    if (m_path == path)
        return;

    m_path = path;

    QByteArray bufferBytes;
    bufferBytes.resize(static_cast<unsigned long>(m_path.size()) * 3 * sizeof(float) );
    float *positions = reinterpret_cast<float*>(bufferBytes.data());
    for(int i=0; i<m_path.size(); i++){
        *positions++ = m_path.at(i).x();
        *positions++ = m_path.at(i).y();
        *positions++ = m_path.at(i).z();
    }

    m_buf->setData(bufferBytes);
    m_positionAttibute->setCount( m_path.size() );

    emit pathChanged(m_path);
}

void PathMesh::push(const QVector3D &point)
{
    auto p = path();
    p.push_back( point );
    setPath( p );
}

void PathMesh::clear()
{
    setPath( QVector<QVector3D>() );
}
