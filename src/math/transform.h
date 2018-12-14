#ifndef UBURU_RENDERENGINE_TRANSFORM_H
#define UBURU_RENDERENGINE_TRANSFORM_H

#include "matrix4x4.h"
#include "vector3d.h"

class Transform {
public:
    virtual Matrix4x4<> Viewport(int x, int y, int width, int height);

    virtual Matrix4x4<> Projection(double coeff);

    virtual Matrix4x4<> LookAt(const Vector3d<> &eye, const Vector3d<> &center, const Vector3d<> &up);
};

#endif // UBURU_RENDERENGINE_TRANSFORM_H