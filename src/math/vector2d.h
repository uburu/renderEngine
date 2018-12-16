#ifndef UBURU_RENDERENGINE_VECTOR2D_H
#define UBURU_RENDERENGINE_VECTOR2D_H

#include "vector3d.h"
#include "detail/MatrixSizeAdapter.h"

template <typename T = double>
class Vector2d : public Vector3d<T> {
public:
    Vector2d();
    Vector2d(T x, T y);
    Vector2d(const Matrix<T> &);
    Vector2d(Matrix<T> &&);
    Vector2d(const Vector2d &) = default;
    Vector2d(Vector2d &&) = default;

    Vector2d &operator=(const Vector2d &) = default;
    Vector2d &operator=(Vector2d &&) = default;

    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);

    void operator+=(const Matrix<T> &rhs);
    void operator-=(const Matrix<T> &rhs);

    Vector2d operator+(T rhs)               const;
    Vector2d operator-(T rhs)               const;
    Vector2d operator*(T rhs)               const;
    Vector2d operator/(T rhs)               const;
    Vector2d operator+(const Vector2d &rhs) const;
    Vector2d operator-(const Vector2d &rhs) const;

    Matrix<T> operator*(const Matrix<T> &rhs) const;

    const Vector2d &operator+() const;
    Vector2d operator-() const;

    template <typename U>
    explicit operator Vector2d<U>() const; 

    bool operator==(const Matrix<T> &) const;
    bool operator!=(const Matrix<T> &) const;

    bool operator==(const Vector2d<T> &) const;
    bool operator!=(const Vector2d<T> &) const;

    template <typename ElementConverter>
    Vector2d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
    Map(ElementConverter) const;

    template <typename U = T>
    Vector2d<U> Rounded() const;

    T &At(size_t i);
    const T &At(size_t i) const;

    Vector2d Normalized() const;

    Vector2d Share() const;

    Matrix<T> AsMatrix(VectorOrientation) const;

protected:
    using MatrixSizeAdapter = detail::MatrixSizeAdapter<2, T>;

private:
    template <typename U>
    friend class Vector2d;

    Vector2d(const Vector3d<T> &);
    Vector2d(Vector3d<T> &&);

    using Vector3d<T>::Cross;
    using Vector3d<T>::GetZ;
    using Vector3d<T>::SetZ;
    using Vector3d<T>::z;
};




/* IMPLEMENTATION */

template <typename T>
Vector2d<T>::Vector2d()
: Vector3d<T>() 
{}

template <typename T>
Vector2d<T>::Vector2d(T x, T y) 
: Vector3d<T>(x, y, 0) 
{}

template <typename T>
Vector2d<T>::Vector2d(const Matrix<T> &other) 
: Vector3d<T>(Vector3d<T>::CreateFromMatrix4x1(detail::MakeVectorFromMatrix<2>(other)))
{}

template <typename T>
Vector2d<T>::Vector2d(Matrix<T> &&other) 
: Vector3d<T>(Vector3d<T>::CreateFromMatrix4x1(detail::MakeVectorFromMatrix<2>(std::move(other)))) 
{}

template <typename T>
Vector2d<T>::Vector2d(const Vector3d<T> &other): Vector3d<T>(other) 
{}

template <typename T>
Vector2d<T>::Vector2d(Vector3d<T> &&other): Vector3d<T>(std::move(other)) 
{}

template <typename T>
void Vector2d<T>::operator+=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector3d<T>::operator+=(rhs);
}

template <typename T>
void Vector2d<T>::operator-=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector3d<T>::operator-=(rhs);
}

template <typename T>
void Vector2d<T>::operator*=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector3d<T>::operator*=(rhs);
}

template <typename T>
void Vector2d<T>::operator/=(T rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector3d<T>::operator/=(rhs);
}


template <typename T>
void Vector2d<T>::operator+=(const Matrix<T> &rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector3d<T>::operator+=(rhs);
}

template <typename T>
void Vector2d<T>::operator-=(const Matrix<T> &rhs) {
    MatrixSizeAdapter adapter(*this);
    Vector3d<T>::operator-=(rhs);
}

template <typename T>
Vector2d<T> Vector2d<T>::operator+(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector2d<T> operator+(T lhs, const Vector2d<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
Vector2d<T> Vector2d<T>::operator-(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator-(rhs));
}

template <typename T>
Vector2d<T> Vector2d<T>::operator*(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator*(rhs));
}

template <typename T>
Vector2d<T> operator*(T lhs, const Vector2d<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
Vector2d<T> Vector2d<T>::operator/(T rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator/(rhs));
}

template <typename T>
Vector2d<T> Vector2d<T>::operator+(const Vector2d &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector2d<T> Vector2d<T>::operator-(const Vector2d &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator-(rhs));
}

template <typename T>
Matrix<T> Vector2d<T>::operator*(const Matrix<T> &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::operator*(rhs));
}


template <typename T>
const Vector2d<T> &Vector2d<T>::operator+() const {
    return *this;
}

template <typename T>
Vector2d<T> Vector2d<T>::operator-() const {
    Vector2d copy(*this);
    copy *= -1;

    return copy;
}

template <typename T>
template <typename U>
Vector2d<T>::operator Vector2d<U>() const {
    return std::move(static_cast<Vector3d<U>>(static_cast<const Vector3d<T> &>(*this)));
} 


template <typename T>
bool Vector2d<T>::operator==(const Matrix<T> &rhs) const {
    MatrixSizeAdapter adapter(*this);
    return Matrix<T>::operator==(rhs);
}

template <typename T>
bool Vector2d<T>::operator!=(const Matrix<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T>
bool Vector2d<T>::operator==(const Vector2d<T> &rhs) const {
    MatrixSizeAdapter adapter(*this);
    MatrixSizeAdapter rhs_adapter(rhs);
    return Matrix<T>::operator==(rhs);
}

template <typename T>
bool Vector2d<T>::operator!=(const Vector2d<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T>
template <typename ElementConverter>
Vector2d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
Vector2d<T>::Map(ElementConverter converter) const {
    MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::Map(converter));
}

template <typename T>
template <typename U>
Vector2d<U> Vector2d<T>::Rounded() const {
    return Map([this](auto &element) {
        if(element < 0) return static_cast<U>(std::ceil(element - 0.5));
        else return static_cast<U>(std::floor(element + 0.5));
    });
}


template <typename T>
T &Vector2d<T>::At(size_t i) {
    MatrixSizeAdapter adapter(*this);
    return Vector3d<T>::At(i);
}

template <typename T>
const T &Vector2d<T>::At(size_t i) const {
    return const_cast<Vector2d<T>*>(this)->At(i);
}

template <typename T>
Vector2d<T> Vector2d<T>::Normalized() const {
    Vector2d copy(*this);
    copy.Normalize();

    return copy;
}

template <typename T>
Vector2d<T> Vector2d<T>::Share() const {
    return std::move(Matrix<T>::Share());
}

template <typename T>
Matrix<T> Vector2d<T>::AsMatrix(VectorOrientation orientation) const {
    auto matrix = Vector3d<T>::AsMatrix(orientation);
    MatrixSizeAdapter adapter(matrix, false);
    return std::move(matrix);
}

#endif // UBURU_RENDERENGINE_VECTOR2D_H