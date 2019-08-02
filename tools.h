#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QVector3D>
#include <QQuaternion>

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = nullptr);

    Q_INVOKABLE QVector3D move(const QVector3D &pose, const QQuaternion &q , const QVector3D &v) const;

signals:

public slots:
};

#endif // TOOLS_H
