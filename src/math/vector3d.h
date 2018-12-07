#ifndef UBURU_RENDERENGINE_VECTOR3D_H
#define UBURU_RENDERENGINE_VECTOR3D_H

#include "vector4d.h"

template <typename T = double>
class Vector3d : public Vector4d<T> {
public:
    Vector3d();
    Vector3d(T x, T y, T z);
    Vector3d(const Matrix<T> &);
    Vector3d(Matrix<T> &&);
    Vector3d(const Vector3d &) = default;
    Vector3d(Vector3d &&) = default;

    Vector3d &operator=(const Vector3d &) = default;
    Vector3d &operator=(Vector3d &&) = default;

    using Matrix<T>::operator*;

    Vector3d operator+(T rhs)               const;
    Vector3d operator-(T rhs)               const;
    Vector3d operator*(T rhs)               const;
    Vector3d operator/(T rhs)               const;
    Vector3d operator+(const Vector3d &rhs) const;
    Vector3d operator-(const Vector3d &rhs) const;

    const Vector3d &operator+() const;
    Vector3d operator-() const;

    template <typename U>
    explicit operator Vector3d<U>() const; 

    template <typename ElementConverter>
    Vector3d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
    Map(ElementConverter) const;

    Vector3d Share() const;

protected:
    template <size_t DIMENSION>
    void AdjustMatrixSize();

private:
    template <typename U>
    friend class Vector3d;

    Vector3d(const Vector4d<T> &);
    Vector3d(Vector4d<T> &&);

    using Vector4d<T>::GetW;
    using Vector4d<T>::SetW;
    using Vector4d<T>::w;
};






/* IMPLEMENTATION */

template <typename T>
Vector3d<T>::Vector3d()
: Vector4d<T>() {
    AdjustMatrixSize<3>();
}

template <typename T>
Vector3d<T>::Vector3d(T x, T y, T z) 
: Vector4d<T>(x, y, z, 0) {
    AdjustMatrixSize<3>();
}

template <typename T>
Vector3d<T>::Vector3d(const Matrix<T> &other) 
: Vector4d<T>(detail::MakeVectorFromMatrix<3>(other)) {
    AdjustMatrixSize<3>();
}

template <typename T>
Vector3d<T>::Vector3d(Matrix<T> &&other) 
: Vector4d<T>(detail::MakeVectorFromMatrix<3>(std::move(other))) {
    AdjustMatrixSize<3>();
}

template <typename T>
Vector3d<T>::Vector3d(const Vector4d<T> &other): Vector4d<T>(other) {
    AdjustMatrixSize<3>();
}

template <typename T>
Vector3d<T>::Vector3d(Vector4d<T> &&other): Vector4d<T>(std::move(other)) {
    AdjustMatrixSize<3>();
}

template <typename T>
Vector3d<T> Vector3d<T>::operator+(T rhs) const {
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector3d<T> operator+(T lhs, const Vector3d<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
Vector3d<T> Vector3d<T>::operator-(T rhs) const {
    return std::move(Matrix<T>::operator-(rhs));
}

template <typename T>
Vector3d<T> Vector3d<T>::operator*(T rhs) const {
    return std::move(Matrix<T>::operator*(rhs));
}

template <typename T>
Vector3d<T> operator*(T lhs, const Vector3d<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
Vector3d<T> Vector3d<T>::operator/(T rhs) const {
    return std::move(Matrix<T>::operator/(rhs));
}

template <typename T>
Vector3d<T> Vector3d<T>::operator+(const Vector3d &rhs) const {
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector3d<T> Vector3d<T>::operator-(const Vector3d &rhs) const {
    return std::move(Matrix<T>::operator-(rhs));
}


template <typename T>
const Vector3d<T> &Vector3d<T>::operator+() const {
    return *this;
}

template <typename T>
Vector3d<T> Vector3d<T>::operator-() const {
    Vector3d copy(*this);
    copy *= -1;

    return copy;
}

template <typename T>
template <typename U>
Vector3d<T>::operator Vector3d<U>() const {
    return std::move(static_cast<const Matrix<U>>(static_cast<const Matrix<T>>(*this)));
} 

template <typename T>
template <typename ElementConverter>
Vector3d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
Vector3d<T>::Map(ElementConverter converter) const {
    return std::move(Matrix<T>::Map(converter));
}

template <typename T>
Vector3d<T> Vector3d<T>::Share() const {
    return std::move(Matrix<T>::Share());
}

template <typename T>
template <size_t DIMENSION>
void Vector3d<T>::AdjustMatrixSize() {
    this->rows -= (this->rows - DIMENSION);
}

#endif // UBURU_RENDERENGINE_VECTOR3D_H