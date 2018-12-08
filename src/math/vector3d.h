#ifndef UBURU_RENDERENGINE_VECTOR3D_H
#define UBURU_RENDERENGINE_VECTOR3D_H

#include "vector4d.h"
#include "detail/MatrixSizeAdapter.h"

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

    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);

    void operator+=(const Matrix<T> &rhs);
    void operator-=(const Matrix<T> &rhs);

    Vector3d operator+(T rhs)               const;
    Vector3d operator-(T rhs)               const;
    Vector3d operator*(T rhs)               const;
    Vector3d operator/(T rhs)               const;
    Vector3d operator+(const Vector3d &rhs) const;
    Vector3d operator-(const Vector3d &rhs) const;

    Matrix<T> operator*(const Matrix<T> &rhs) const;

    const Vector3d &operator+() const;
    Vector3d operator-() const;

    template <typename U>
    explicit operator Vector3d<U>() const; 

    bool operator==(const Matrix<T> &) const;
    bool operator!=(const Matrix<T> &) const;

    bool operator==(const Vector3d<T> &) const;
    bool operator!=(const Vector3d<T> &) const;

    template <typename ElementConverter>
    Vector3d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
    Map(ElementConverter) const;

    Vector3d Share() const;

    Matrix<T> AsMatrix(VectorOrientation) const;

private:
    using MatrixSizeAdapter = detail::MatrixSizeAdapter<3, T>;

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
: Vector4d<T>() 
{}

template <typename T>
Vector3d<T>::Vector3d(T x, T y, T z) 
: Vector4d<T>(x, y, z, 0) 
{}

template <typename T>
Vector3d<T>::Vector3d(const Matrix<T> &other) 
: Vector4d<T>(detail::MakeVectorFromMatrix<3>(other)) 
{}

template <typename T>
Vector3d<T>::Vector3d(Matrix<T> &&other) 
: Vector4d<T>(detail::MakeVectorFromMatrix<3>(std::move(other))) 
{}

template <typename T>
Vector3d<T>::Vector3d(const Vector4d<T> &other): Vector4d<T>(other) 
{}

template <typename T>
Vector3d<T>::Vector3d(Vector4d<T> &&other): Vector4d<T>(std::move(other)) 
{}

template <typename T>
void Vector3d<T>::operator+=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector4d<T>::operator+=(rhs);
}

template <typename T>
void Vector3d<T>::operator-=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector4d<T>::operator-=(rhs);
}

template <typename T>
void Vector3d<T>::operator*=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector4d<T>::operator*=(rhs);
}

template <typename T>
void Vector3d<T>::operator/=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector4d<T>::operator/=(rhs);
}


template <typename T>
void Vector3d<T>::operator+=(const Matrix<T> &rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector4d<T>::operator+=(rhs);
}

template <typename T>
void Vector3d<T>::operator-=(const Matrix<T> &rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector4d<T>::operator-=(rhs);
}

template <typename T>
Vector3d<T> Vector3d<T>::operator+(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector3d<T> operator+(T lhs, const Vector3d<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
Vector3d<T> Vector3d<T>::operator-(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator-(rhs));
}

template <typename T>
Vector3d<T> Vector3d<T>::operator*(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator*(rhs));
}

template <typename T>
Vector3d<T> operator*(T lhs, const Vector3d<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
Vector3d<T> Vector3d<T>::operator/(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator/(rhs));
}

template <typename T>
Vector3d<T> Vector3d<T>::operator+(const Vector3d &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector3d<T> Vector3d<T>::operator-(const Vector3d &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator-(rhs));
}

template <typename T>
Matrix<T> Vector3d<T>::operator*(const Matrix<T> &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator*(rhs));
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
    return std::move(static_cast<Vector4d<U>>(static_cast<const Vector4d<T> &>(*this)));
} 


template <typename T>
bool Vector3d<T>::operator==(const Matrix<T> &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return Matrix<T>::operator==(rhs);
}

template <typename T>
bool Vector3d<T>::operator!=(const Matrix<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T>
bool Vector3d<T>::operator==(const Vector3d<T> &rhs) const {
    MatrixSizeAdapter adapter(*this);
    MatrixSizeAdapter rhs_adapter(rhs);
    return Matrix<T>::operator==(rhs);
}

template <typename T>
bool Vector3d<T>::operator!=(const Vector3d<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T>
template <typename ElementConverter>
Vector3d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
Vector3d<T>::Map(ElementConverter converter) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::Map(converter));
}

template <typename T>
Vector3d<T> Vector3d<T>::Share() const {
    return std::move(Matrix<T>::Share());
}

template <typename T>
Matrix<T> Vector3d<T>::AsMatrix(VectorOrientation orientation) const {
    auto matrix = Vector4d<T>::AsMatrix(orientation);
    MatrixSizeAdapter adapter(matrix, false);
    return std::move(matrix);
}

#endif // UBURU_RENDERENGINE_VECTOR3D_H