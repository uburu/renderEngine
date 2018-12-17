#ifndef UBURU_REDNERENGINE_MATH_UTIL_H
#define UBURU_REDNERENGINE_MATH_UTIL_H

#include "vector3d.h"
#include "vector2d.h"

Vector3d<> Barycentric(const Vector2d<> &a, const Vector2d<> &b, const Vector2d<> &c, const Vector2d<int> &position);

Vector3d<> Barycentric(const Matrix<> &, const Vector2d<int> &position);

#endif // UBURU_REDNERENGINE_MATH_UTIL_H
