#ifndef LINEMESH_H
#define LINEMESH_H

#include <QGeometryRenderer>
#include <QVector3D>
#include <Qt3DRender>

class LineMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(QVector3D from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QVector3D to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(float thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)

public:
    explicit LineMesh(Qt3DCore::QNode *parent = nullptr);

    QVector3D from() const;
    QVector3D to() const;    
    float thickness() const;

private:
    QVector3D m_from;
    QVector3D m_to;
    Qt3DRender::QBuffer *m_buf = Q_NULLPTR;

    float m_thickness = 1.0f;

signals:
    void fromChanged(QVector3D from);
    void toChanged(QVector3D to);
    void thicknessChanged(float thickness);

public slots:
    void setFrom(QVector3D from);
    void setTo(QVector3D to);
    void setThickness(float thickness);
};

#endif // LINEMESH_H
