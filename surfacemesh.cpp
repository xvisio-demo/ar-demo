#include "surfacemesh.h"

#include <QBufferDataGenerator>


namespace {

QByteArray createSurfaceVertexData(Surface surface)
{
    const int nVerts = surface.points.size();
    QByteArray bufferBytes;
    const quint32 elementSize = 3 * sizeof(float);
    bufferBytes.resize(elementSize * nVerts);

    float *positions = reinterpret_cast<float*>(bufferBytes.data());

    for(int i=0;i<surface.points.size();i++){
        *positions++ = surface.points.at(i).x();
        *positions++ = surface.points.at(i).y();
        *positions++ = surface.points.at(i).z();
    }

    return bufferBytes;
}

QByteArray createSurfaceIndexData(Surface surface)
{
    int sum = 0;
    for( int i=0; i<surface.indexes.size(); i++){
        sum += surface.indexes.at(i).points_index.size();
    }
    const int indices = sum;
    Q_ASSERT(indices < std::numeric_limits<quint16>::max());
    QByteArray indexBytes;
    indexBytes.resize(indices * sizeof(quint16));
    quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

    for(int i=0; i<surface.indexes.size(); i++){
        for(int j=0; j<surface.indexes.at(i).points_index.size();j++){
            *indexPtr++ = surface.indexes.at(i).points_index.at(j);
        }
    }

    return indexBytes;
}

};

class SurfaceVertexBufferFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
    explicit SurfaceVertexBufferFunctor(Surface surface) : m_surface(surface) {}
    ~SurfaceVertexBufferFunctor() override {}

    QByteArray operator()() final {
        return createSurfaceVertexData(m_surface);
    }

    bool operator ==(const Qt3DRender::QBufferDataGenerator &other) const final {
        const SurfaceVertexBufferFunctor *otherFunctor = functor_cast<SurfaceVertexBufferFunctor>(&other);
        if (otherFunctor != nullptr)
            return otherFunctor->m_surface == m_surface;
        return false;
    }

    QT3D_FUNCTOR(SurfaceVertexBufferFunctor)

    private:
        Surface m_surface;
};


class SurfaceIndexBufferFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
    explicit SurfaceIndexBufferFunctor(Surface surface) : m_surface(surface) {}
    ~SurfaceIndexBufferFunctor() override {}

    QByteArray operator()() final {
        return createSurfaceIndexData( m_surface );
    }

    bool operator ==(const Qt3DRender::QBufferDataGenerator &other) const final {
        const SurfaceIndexBufferFunctor *otherFunctor = functor_cast<SurfaceIndexBufferFunctor>(&other);
        if (otherFunctor != nullptr)
            return otherFunctor->m_surface == m_surface;
        return false;
    }

    QT3D_FUNCTOR(SurfaceIndexBufferFunctor)

    private:
        Surface m_surface;
};


SurfaceMesh::SurfaceMesh(Qt3DCore::QNode *parent) : QGeometryRenderer(parent)
{
    auto *geometry = new Qt3DRender::QGeometry(this);
    m_vertexBuffer = new Qt3DRender::QBuffer(geometry);
    m_indexBuffer = new Qt3DRender::QBuffer(geometry);

    const int positionStride = 3;
    const int texStride = 0; //2;
    const int normalStride = 0; //3
    const int tangentStride = 0; //4;
    const int stride = (positionStride + texStride + normalStride + tangentStride) * sizeof(float);

    m_positionAttribute = new Qt3DRender::QAttribute(geometry);
    m_positionAttribute->setName( Qt3DRender::QAttribute::defaultPositionAttributeName()) ;
    m_positionAttribute->setAttributeType( Qt3DRender::QAttribute::VertexAttribute );
    m_positionAttribute->setVertexBaseType( Qt3DRender::QAttribute::Float );
    m_positionAttribute->setVertexSize( 3 );
    m_positionAttribute->setBuffer( m_vertexBuffer );
    m_positionAttribute->setByteStride( stride );
    m_positionAttribute->setCount( 0 );

   /* m_normalAttribute = new Qt3DRender::QAttribute(geometry);
    m_normalAttribute->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());
    m_normalAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_normalAttribute->setVertexSize(3);
    m_normalAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_normalAttribute->setBuffer(m_vertexBuffer);
    m_normalAttribute->setByteStride(stride);
    m_normalAttribute->setByteOffset(5 * sizeof(float));
    m_normalAttribute->setCount(0);*/

    m_indexAttribute = new Qt3DRender::QAttribute(geometry);
    m_indexAttribute->setAttributeType( Qt3DRender::QAttribute::IndexAttribute );
    m_indexAttribute->setVertexBaseType( Qt3DRender::QAttribute::UnsignedShort );
    m_indexAttribute->setBuffer( m_indexBuffer );
    m_indexAttribute->setCount( 0 );

    m_vertexBuffer->setDataGenerator(QSharedPointer<SurfaceVertexBufferFunctor>::create(m_surface));
    m_indexBuffer->setDataGenerator(QSharedPointer<SurfaceIndexBufferFunctor>::create(m_surface));

    geometry->addAttribute(m_positionAttribute);
    //geometry->addAttribute(m_normalAttribute);
    geometry->addAttribute(m_indexAttribute);

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
    this->setGeometry( geometry );
}

Surface SurfaceMesh::surface() const
{
    return m_surface;
}

void SurfaceMesh::updateVertices()
{
    qDebug() << "m_surface.points.size()" << m_surface.points.size();
    m_positionAttribute->setCount( m_surface.points.size() );
    m_vertexBuffer->setDataGenerator(QSharedPointer<SurfaceVertexBufferFunctor>::create(m_surface));
}

void SurfaceMesh::updateIndices()
{
    int sum = 0;
    for( int i=0; i<m_surface.indexes.size(); i++){
        sum += m_surface.indexes.at(i).points_index.size();
    }
    qDebug() << "sum" << sum;
    m_indexBuffer->setDataGenerator(QSharedPointer<SurfaceIndexBufferFunctor>::create(m_surface));
    m_indexAttribute->setCount( sum );
}

void SurfaceMesh::setSurface(Surface surface)
{
    qDebug() << surface;
    m_surface = surface;
    updateVertices();
    updateIndices();
    emit surfaceChanged(m_surface);
}
