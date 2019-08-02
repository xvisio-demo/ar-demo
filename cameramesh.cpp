#include "cameramesh.h"

#include <QBufferDataGenerator>


namespace {

QByteArray createCameraVertexData(float w, float h, float d)
{
    Q_ASSERT(w > 0.0f);
    Q_ASSERT(h > 0.0f);
    Q_ASSERT(d > 0.0f);

    const int nVerts = 5;
    QByteArray bufferBytes;
    const quint32 elementSize = 3 * sizeof(float);
    bufferBytes.resize(elementSize * nVerts);

    float *positions = reinterpret_cast<float*>(bufferBytes.data());

    *positions++ = 0.f;
    *positions++ = 0.f;
    *positions++ = 0.f;

    *positions++ =  0.5f * w;
    *positions++ =  0.5f * h;
    *positions++ = d;
    *positions++ = -0.5f * w;
    *positions++ =  0.5f * h;
    *positions++ = d;
    *positions++ = -0.5f * w;
    *positions++ = -0.5f * h;
    *positions++ = d;
    *positions++ =  0.5f * w;
    *positions++ = -0.5f * h;
    *positions++ = d;

    return bufferBytes;
}

QByteArray createCameraIndexData()
{
    const int indices = 16;
    Q_ASSERT(indices < std::numeric_limits<quint16>::max());
    QByteArray indexBytes;
    indexBytes.resize(indices * sizeof(quint16));
    quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

    *indexPtr++ = 0;
    *indexPtr++ = 1;
    *indexPtr++ = 0;
    *indexPtr++ = 2;
    *indexPtr++ = 0;
    *indexPtr++ = 3;
    *indexPtr++ = 0;
    *indexPtr++ = 4;
    *indexPtr++ = 1;
    *indexPtr++ = 2;
    *indexPtr++ = 2;
    *indexPtr++ = 3;
    *indexPtr++ = 3;
    *indexPtr++ = 4;
    *indexPtr++ = 4;
    *indexPtr++ = 1;

    return indexBytes;
}

};

class CameraVertexBufferFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
    explicit CameraVertexBufferFunctor(float w, float h, float depth) : m_width(w), m_height(h), m_depth(depth) {}
    ~CameraVertexBufferFunctor() override {}

    QByteArray operator()() final {
        return createCameraVertexData(m_width, m_height, m_depth);
    }

    bool operator ==(const Qt3DRender::QBufferDataGenerator &other) const final {
        const CameraVertexBufferFunctor *otherFunctor = functor_cast<CameraVertexBufferFunctor>(&other);
        if (otherFunctor != nullptr)
            return (otherFunctor->m_width == m_width &&
                    otherFunctor->m_height == m_height &&
                    otherFunctor->m_depth == m_depth);
        return false;
    }

    QT3D_FUNCTOR(CameraVertexBufferFunctor)

    private:
        float m_width;
        float m_height;
        float m_depth;
};


class CameraIndexBufferFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
    explicit CameraIndexBufferFunctor() {}
    ~CameraIndexBufferFunctor() override {}

    QByteArray operator()() final {
        return createCameraIndexData();
    }

    bool operator ==(const Qt3DRender::QBufferDataGenerator &other) const final {
        const CameraIndexBufferFunctor *otherFunctor = functor_cast<CameraIndexBufferFunctor>(&other);
        if (otherFunctor != nullptr)
            return true;
        return false;
    }

    QT3D_FUNCTOR(CameraIndexBufferFunctor)
};


CameraMesh::CameraMesh(Qt3DCore::QNode *parent) : Qt3DRender::QGeometryRenderer(parent)
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
    m_positionAttribute->setCount( 5 );

    m_indexAttribute = new Qt3DRender::QAttribute(geometry);
    m_indexAttribute->setAttributeType( Qt3DRender::QAttribute::IndexAttribute );
    m_indexAttribute->setVertexBaseType( Qt3DRender::QAttribute::UnsignedShort );
    m_indexAttribute->setBuffer( m_indexBuffer );
    m_indexAttribute->setCount( 16 );

    m_vertexBuffer->setDataGenerator(QSharedPointer<CameraVertexBufferFunctor>::create(m_width, m_height, m_depth));
    m_indexBuffer->setDataGenerator(QSharedPointer<CameraIndexBufferFunctor>::create());

    geometry->addAttribute(m_positionAttribute);
    geometry->addAttribute(m_indexAttribute);

    this->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    this->setGeometry( geometry );
}

float CameraMesh::width() const
{
    return m_width;
}

float CameraMesh::height() const
{
    return m_height;
}

float CameraMesh::depth() const
{
    return m_depth;
}

void CameraMesh::updateVertices()
{
    m_vertexBuffer->setDataGenerator(QSharedPointer<CameraVertexBufferFunctor>::create(m_width, m_height, m_depth));
}

void CameraMesh::setWidth(float width)
{
    if (qFuzzyCompare(m_width, width))
        return;

    m_width = width;
    updateVertices();
    emit widthChanged(m_width);
}

void CameraMesh::setHeight(float height)
{
    if (qFuzzyCompare(m_height, height))
        return;

    m_height = height;
    updateVertices();
    emit heightChanged(m_height);
}

void CameraMesh::setDepth(float depth)
{
    if (qFuzzyCompare(m_depth, depth))
        return;

    m_depth = depth;
    updateVertices();
    emit depthChanged(m_depth);
}
