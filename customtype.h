#ifndef CUSTOMTYPE_H
#define CUSTOMTYPE_H

#include <QVector>
#include <QVector3D>
#include <QDebug>

struct SurfaceIndexes
{
    QVector<int> points_index;
    QVector<int> vertex_index;
    int face_index;
};

struct Surface
{
    QVector<QVector3D> points;
    QVector<QVector3D> vertexNormals;
    QVector<QVector3D> faceNormals;

    QVector<SurfaceIndexes> indexes;
};

struct Voxels
{
    QVector<QVector3D> voxels;
    double size;
};

QDebug operator<< (QDebug d, const SurfaceIndexes &model);
QDebug operator<< (QDebug d, const Surface &model);

bool operator==(const SurfaceIndexes& si1, const SurfaceIndexes& si2);
bool operator==(const Surface& s1, const Surface& s2);

bool operator==(const Voxels& s1, const Voxels& s2);

#endif // CUSTOMTYPE_H
