#include "transform.h"

Matrix4x4<> Transform::Viewport(int x, int y, int width, int height) {
    Matrix4x4<> result = Matrix4x4<>::Identity();

    result.At(0, 3) = x + width/2.0;
    result.At(1, 3) = y + height/2.0;
    result.At(2, 3) = 1.0;
    result.At(0, 0) = width/2.0;
    result.At(1, 1) = height/2.0;
    result.At(2, 2) = 0;

    return result;
}

Matrix4x4<> Transform::Projection(double coeff) {
    auto result = Matrix4x4<>::Identity();
    result.At(3, 2) = coeff;

    return result;
}

Matrix4x4<> Transform::LookAt(const Vector3d<> &eye, const Vector3d<> &center, const Vector3d<> &up) {
    auto z = (eye-center).Normalized();
    auto x = up.Cross(z).Normalized();
    auto y = z.Cross(x).Normalized();
    auto Minv = Matrix4x4<>::Identity();
    auto Tr   = Matrix4x4<>::Identity();

    auto orientation = VectorOrientation::kVertical;
    auto X = x.AsMatrix(orientation);
    auto Y = y.AsMatrix(orientation);
    auto Z = z.AsMatrix(orientation);
    auto C = center.AsMatrix(orientation);

    for (int i=0; i<3; i++) {
        Minv.At(0, i) = X.At(i, 0);
        Minv.At(1, i) = Y.At(i, 0);
        Minv.At(2, i) = Z.At(i, 0);
        Tr.At(i, 3) = -C.At(i, 0);
    }

    return Minv*Tr;
}