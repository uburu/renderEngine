#include "util.h"

Vector3d<> Barycentric(const Vector2d<> &a, const Vector2d<> &b, const Vector2d<> &c, const Vector2d<> &position) {
    auto orientation = VectorOrientation::kVertical;
    auto A = a.AsMatrix(orientation);
    auto B = b.AsMatrix(orientation);
    auto C = c.AsMatrix(orientation);
    auto P = position.AsMatrix(orientation);
    
    Vector3d<> s[2];
    
    for (int i=2; i--; ) {
        s[i].x() = C.At(i, 0) - A.At(i, 0);
        s[i].y() = B.At(i, 0) - A.At(i, 0);
        s[i].z() = A.At(i, 0) - P.At(i, 0);
    }
    auto u = s[0].Cross(s[1]);
    if (std::abs(u.z()) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vector3d<>(1.f-(u.x()+u.y())/u.z(), u.y()/u.z(), u.x()/u.z());
    return Vector3d<>(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}