#include "gridmesh.h"

#include <QBufferDataGenerator>


namespace {

QByteArray createGridVertexData(float w, float h, QSize resolution)
{
    Q_ASSERT(w > 0.0f);
    Q_ASSERT(h > 0.0f);
    Q_ASSERT(resolution.width() > 0);
    Q_ASSERT(resolution.height() > 0);

    const int nVerts = ((resolution.width()+1)*(resolution.height()+1));
    QByteArray bufferBytes;
    const quint32 elementSize = 3 * sizeof(float);
    bufferBytes.resize(elementSize * nVerts);

    float *positions = reinterpret_cast<float*>(bufferBytes.data());

    float sx = w / resolution.width();
    float sz = h / resolution.height();

    for(int i=0;i<resolution.width()+1;i++){
        for(int j=0;j<resolution.height()+1;j++){
            *positions++ = i * sx;
            *positions++ = 0.f;
            *positions++ = j * sz;
        }
    }

    return bufferBytes;
}

QByteArray createGridIndexData(QSize resolution)
{
    const int indices = 2 * (resolution.width() + resolution.height() +4);
    Q_ASSERT(indices < std::numeric_limits<quint16>::max());
    QByteArray indexBytes;
    indexBytes.resize(indices * sizeof(quint16));
    quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

    int h = resolution.height()+1;
    for(int i=0; i<resolution.width()+1; i++){
        *indexPtr++ = i * h;
        *indexPtr++ = (i+1)*h-1;
    }
    int w = ((resolution.width()+1)*(resolution.height()+1));
    for(int i=0; i<resolution.height()+1; i++){
        *indexPtr++ = i ;
        *indexPtr++ = w - h + i;
    }
    return indexBytes;
}

};

class GridVertexBufferFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
    explicit GridVertexBufferFunctor(float w, float h, QSize resolution) : m_width(w), m_height(h), m_resolution(resolution) {}
    ~GridVertexBufferFunctor() override {}

    QByteArray operator()() final {
        return createGridVertexData(m_width, m_height, m_resolution);
    }

    bool operator ==(const Qt3DRender::QBufferDataGenerator &other) const final {
        const GridVertexBufferFunctor *otherFunctor = functor_cast<GridVertexBufferFunctor>(&other);
        if (otherFunctor != nullptr)
            return (otherFunctor->m_width == m_width &&
                    otherFunctor->m_height == m_height &&
                    otherFunctor->m_resolution == m_resolution);
        return false;
    }

    QT3D_FUNCTOR(GridVertexBufferFunctor)

    private:
        float m_width;
        float m_height;
        QSize m_resolution;
};


class GridIndexBufferFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
    explicit GridIndexBufferFunctor(QSize resolution): m_resolution(resolution) {}
    ~GridIndexBufferFunctor() override {}

    QByteArray operator()() final {
        return createGridIndexData( m_resolution );
    }

    bool operator ==(const Qt3DRender::QBufferDataGenerator &other) const final {
        const GridIndexBufferFunctor *otherFunctor = functor_cast<GridIndexBufferFunctor>(&other);
        if (otherFunctor != nullptr)
            return otherFunctor->m_resolution == m_resolution;
        return false;
    }

    QT3D_FUNCTOR(GridIndexBufferFunctor)

    private:
        QSize m_resolution;
};


GridMesh::GridMesh(Qt3DCore::QNode *parent) : QGeometryRenderer(parent)
{
    auto *geometry = new Qt3DRender::QGeometry(this);
    m_vertexBuffer = new Qt3DRender::QBuffer(geometry);
    m_indexBuffer = new Qt3DRender::QBuffer(geometry);

    m_positionAttribute = new Qt3DRender::QAttribute(geometry);
    m_positionAttribute->setName( Qt3DRender::QAttribute::defaultPositionAttributeName()) ;
    m_positionAttribute->setAttributeType( Qt3DRender::QAttribute::VertexAttribute );
    m_positionAttribute->setVertexBaseType( Qt3DRender::QAttribute::Float );
    m_positionAttribute->setVertexSize( 3 );
    m_positionAttribute->setBuffer( m_vertexBuffer );
    m_positionAttribute->setByteStride( 3 * sizeof(float) );
    m_positionAttribute->setCount( (m_resolution.width()+1)*(m_resolution.height()+1) );

    m_indexAttribute = new Qt3DRender::QAttribute(geometry);
    m_indexAttribute->setAttributeType( Qt3DRender::QAttribute::IndexAttribute );
    m_indexAttribute->setVertexBaseType( Qt3DRender::QAttribute::UnsignedShort );
    m_indexAttribute->setBuffer( m_indexBuffer );
    m_indexAttribute->setCount( 2 * (m_resolution.width() + m_resolution.height() + 4) );

    m_vertexBuffer->setDataGenerator(QSharedPointer<GridVertexBufferFunctor>::create(m_width, m_height, m_resolution));
    m_indexBuffer->setDataGenerator(QSharedPointer<GridIndexBufferFunctor>::create(m_resolution));

    geometry->addAttribute(m_positionAttribute);
    geometry->addAttribute(m_indexAttribute);

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    this->setGeometry( geometry );
}

float GridMesh::width() const
{
    return m_width;
}

float GridMesh::height() const
{
    return m_height;
}

QSize GridMesh::resolution() const
{
    return m_resolution;
}

void GridMesh::updateVertices()
{
    const int nVerts = (m_resolution.width()+1)*(m_resolution.height()+1);
    m_positionAttribute->setCount(nVerts);
    m_vertexBuffer->setDataGenerator(QSharedPointer<GridVertexBufferFunctor>::create(m_width, m_height, m_resolution));
}

void GridMesh::updateIndices()
{
    m_indexAttribute->setCount(2 * (m_resolution.width() + m_resolution.height() + 4));
    m_indexBuffer->setDataGenerator(QSharedPointer<GridIndexBufferFunctor>::create(m_resolution));

}

void GridMesh::setWidth(float width)
{
    if (qFuzzyCompare(m_width, width))
        return;

    m_width = width;
    updateVertices();
    emit widthChanged(m_width);
}

void GridMesh::setHeight(float height)
{
    if (qFuzzyCompare(m_height, height))
        return;

    m_height = height;
    updateVertices();
    emit heightChanged(m_height);
}

void GridMesh::setResolution(QSize resolution)
{
    if (m_resolution == resolution)
        return;

    m_resolution = resolution;
    updateVertices();
    updateIndices();
    emit resolutionChanged(m_resolution);
}
