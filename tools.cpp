#include "tools.h"

Tools::Tools(QObject *parent) : QObject(parent)
{

}

QVector3D Tools::move(const QVector3D &pose, const QQuaternion &q, const QVector3D &v) const
{
    return pose + q.rotatedVector( v );
}
