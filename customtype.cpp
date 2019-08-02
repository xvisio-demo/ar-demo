#include "customtype.h"

QDebug operator<< (QDebug d, const SurfaceIndexes &model)
{
    d << "points_index:" << model.points_index << "\n";
    d << "vertex_index:" << model.vertex_index << "\n";
    d << "face_index:" << model.face_index << "\n";
    return d;
}

QDebug operator<< (QDebug d, const Surface &model)
{
    d << "points:" << model.points << "\n";
    d << "vertexNormals:" << model.vertexNormals << "\n";
    d << "faceNormals:" << model.faceNormals << "\n";
    d << "indexes" << model.indexes << "\n";
    return d;
}

bool operator==(const SurfaceIndexes &si1, const SurfaceIndexes &si2)
{
    if( si1.points_index != si2.points_index ) return false;
    if( si1.vertex_index != si2.vertex_index ) return false;
    if( si1.face_index != si2.face_index ) return false;
    return true;
}

bool operator==(const Surface &s1, const Surface &s2)
{
    if( s1.points != s2.points ) return false;
    if( s1.vertexNormals != s2.vertexNormals ) return false;
    if( s1.faceNormals != s2.faceNormals ) return false;
    if( s1.indexes != s2.indexes ) return false;
    return true;
}

bool operator==(const Voxels &s1, const Voxels &s2)
{
    if( s1.size != s2.size ) return false;
    if( s1.voxels != s2.voxels ) return false;
    return true;
}
