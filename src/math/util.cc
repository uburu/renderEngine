#include "util.h"

Vector3d<> Barycentric(const Vector2d<> &a, const Vector2d<> &b, const Vector2d<> &c, const Vector2d<int> &p) {    
    Vector3d<> s[2];
    
    for (int i=2; i--; ) {
        s[i].x() = c.At(i) - a.At(i);
        s[i].y() = b.At(i) - a.At(i);
        s[i].z() = a.At(i) - p.At(i);
    }
    auto u = s[0].Cross(s[1]);
    if (std::abs(u.z()) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vector3d<>(1.f-(u.x()+u.y())/u.z(), u.y()/u.z(), u.x()/u.z());
    return Vector3d<>(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

Vector3d<> Barycentric(const Matrix<> &m, const Vector2d<int> &p) {
    Vector3d<> s[2];
    
    for (int i=2; i--; ) {
        s[i].x() = m.At(2, i) - m.At(0, i);
        s[i].y() = m.At(1, i) - m.At(0, i);
        s[i].z() = m.At(0, i) - p.At(i);
    }
    auto u = s[0].Cross(s[1]);
    if (std::abs(u.z()) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vector3d<>(1.f-(u.x()+u.y())/u.z(), u.y()/u.z(), u.x()/u.z());
    return Vector3d<>(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}