#ifndef UBURU_RENDERENGINE_VECTOR4D_H
#define UBURU_RENDERENGINE_VECTOR4D_H

#include "matrix.h"

enum VectorOrientation {
    kVertical,
    kHorizontal
};

template <typename T = double>
class Vector4d : public Matrix<T> {
    using Matrix<T>::GetRows;
    using Matrix<T>::GetColumns;
    using Matrix<T>::At;
    using Matrix<T>::Transpose;
    using Matrix<T>::Transposed;
    using Matrix<T>::Share;
    using Matrix<T>::Identity;
    using Matrix<T>::Zero;
    using Matrix<T>::Diagonal;
    using Matrix<T>::Square;
    using Matrix<T>::operator*=;
public:
    Vector4d();
    Vector4d(T x, T y, T z, T w);
    Vector4d(const Matrix<T> &);
    Vector4d(Matrix<T> &&);
    Vector4d(const Vector4d &) = default;
    Vector4d(Vector4d &&) = default;

    Vector4d &operator=(const Vector4d &) = default;
    Vector4d &operator=(Vector4d &&) = default;

    using Matrix<T>::operator*;

    void operator*=(T rhs);

    Vector4d operator+(T rhs)               const;
    Vector4d operator-(T rhs)               const;
    Vector4d operator*(T rhs)               const;
    Vector4d operator/(T rhs)               const;
    Vector4d operator+(const Vector4d &rhs) const;
    Vector4d operator-(const Vector4d &rhs) const;

    const Vector4d &operator+() const;
    Vector4d operator-() const;

    template <typename U>
    explicit operator Vector4d<U>() const; 

    template <typename ElementConverter>
    Vector4d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
    Map(ElementConverter) const;

    template <typename U = T>
    Vector4d<U> Rounded() const;

    T &At(size_t i);
    const T &At(size_t i) const;

    T GetX() const;
    T GetY() const;
    T GetZ() const;
    T GetW() const;

    void SetX(T);
    void SetY(T);
    void SetZ(T);
    void SetW(T);

    const T &x() const;
    const T &y() const;
    const T &z() const;
    const T &w() const;

    T &x();
    T &y();
    T &z();
    T &w();

    Vector4d &x(T);
    Vector4d &y(T);
    Vector4d &z(T);
    Vector4d &w(T);

    T Dot(const Vector4d &) const;

    T Norm() const;
    double Length() const;
    void Normalize();
    Vector4d Normalized() const;

    Vector4d Share() const;

    Matrix<T> AsMatrix(VectorOrientation) const;
};

/* IMPLEMENTATION */

namespace detail {
    template <size_t DIMENSION = 4, typename T = double>
    Matrix<T> MakeVectorFromMatrix(const Matrix<T> &other) {
        assert(
            (other.GetRows() == DIMENSION && other.GetColumns() == 1)
            || (other.GetRows() == 1 && other.GetColumns() == DIMENSION)
            && "Invalid Matrix size for Vector4d"
        );

        Matrix<T> matrix = ((other.GetRows() == DIMENSION && other.GetColumns() == 1)?
                      std::move(other.Share())
                      : other.Transposed());

        if constexpr(DIMENSION < 4) {
            Matrix<T> result(4, 1, 0, MatrixOrder::kRowMajor);
            
            for(size_t i = 0; i < DIMENSION; ++i)
                result.At(i, 0) = matrix.At(i, 0);
            matrix = std::move(result);        
        }

        return matrix;     
    }

    template <size_t DIMENSION, typename T>
    Matrix<T> MakeVectorFromMatrix(Matrix<T> &&other) {
        assert(
            (other.GetRows() == DIMENSION && other.GetColumns() == 1)
            || (other.GetRows() == 1 && other.GetColumns() == DIMENSION)
            && "Invalid Matrix size for Vector4d"
        );

        if(other.GetRows() == 1 && other.GetColumns() == DIMENSION) other.Transpose();


        if constexpr(DIMENSION < 4) {
            Matrix<T> result(4, 1, 0, MatrixOrder::kRowMajor);
            
            for(size_t i = 0; i < DIMENSION; ++i)
                result.At(i, 0) = other.At(i, 0);
            return std::move(result);
        } else {
            return std::move(other);
        }
    }
}

template <typename T>
Vector4d<T>::Vector4d() 
: Matrix<T>(4, 1, 0, MatrixOrder::kRowMajor)
{}

template <typename T>
Vector4d<T>::Vector4d(T x, T y, T z, T w) 
: Vector4d() {
    this->x() = x;
    this->y() = y;
    this->z() = z;
    this->w() = w;
}

template <typename T>
Vector4d<T>::Vector4d(const Matrix<T> &other)
: Matrix<T>(detail::MakeVectorFromMatrix(other)) {
}

template <typename T>
Vector4d<T>::Vector4d(Matrix<T> &&other)
: Matrix<T>(detail::MakeVectorFromMatrix(std::move(other))) {
    assert(other.GetRows() == 4 && other.GetColumns() == 1 && "Invalid Matrix size for Vector4d");
}

template <typename T>
void Vector4d<T>::operator*=(T rhs) {
    return Matrix<T>::operator*=(rhs);
}

template <typename T>
Vector4d<T> Vector4d<T>::operator+(T rhs) const {
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector4d<T> operator+(T lhs, const Vector4d<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
Vector4d<T> Vector4d<T>::operator-(T rhs) const {
    return std::move(Matrix<T>::operator-(rhs));
}

template <typename T>
Vector4d<T> Vector4d<T>::operator*(T rhs) const {
    return std::move(Matrix<T>::operator*(rhs));
}

template <typename T>
Vector4d<T> operator*(T lhs, const Vector4d<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
Vector4d<T> Vector4d<T>::operator/(T rhs) const {
    return std::move(Matrix<T>::operator/(rhs));
}

template <typename T>
Vector4d<T> Vector4d<T>::operator+(const Vector4d &rhs) const {
    return std::move(Matrix<T>::operator+(rhs));
}

template <typename T>
Vector4d<T> Vector4d<T>::operator-(const Vector4d &rhs) const {
    return std::move(Matrix<T>::operator-(rhs));
}


template <typename T>
const Vector4d<T> &Vector4d<T>::operator+() const {
    return *this;
}

template <typename T>
Vector4d<T> Vector4d<T>::operator-() const {
    Vector4d copy(*this);
    copy *= -1;

    return copy;
}


template <typename T>
template <typename U>
Vector4d<T>::operator Vector4d<U>() const {
    return std::move(static_cast<const Matrix<U>>(static_cast<const Matrix<T> &>(*this)));
} 

template <typename T>
template <typename ElementConverter>
Vector4d<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
Vector4d<T>::Map(ElementConverter converter) const {
    return std::move(Matrix<T>::Map(converter));
}

template <typename T>
template <typename U>
Vector4d<U> Vector4d<T>::Rounded() const {
    return Map([this](auto &element) {
        if(element < 0) return static_cast<U>(std::ceil(element - 0.5));
        else return static_cast<U>(std::floor(element + 0.5));
    });
}

template <typename T>
T &Vector4d<T>::At(size_t i) {
    return Matrix<T>::At(i, 0);
}

template <typename T>
const T &Vector4d<T>::At(size_t i) const {
    return const_cast<Vector4d<T>*>(this)->At(i);
}

template <typename T>
T Vector4d<T>::GetX() const {
    return x();
}

template <typename T>
T Vector4d<T>::GetY() const {
    return y();
}

template <typename T>
T Vector4d<T>::GetZ() const {
    return z();
}

template <typename T>
T Vector4d<T>::GetW() const {
    return w();
}


template <typename T>
void Vector4d<T>::SetX(T x) {
    Matrix<T>::At(0, 0) = x;
}

template <typename T>
void Vector4d<T>::SetY(T y) {
    Matrix<T>::At(1, 0) = y;
}

template <typename T>
void Vector4d<T>::SetZ(T z) {
    Matrix<T>::At(2, 0) = z;
}

template <typename T>
void Vector4d<T>::SetW(T w) {
    Matrix<T>::At(3, 0) = w;
}


template <typename T>
const T &Vector4d<T>::x() const {
    return const_cast<Vector4d*>(this)->x();
}

template <typename T>
const T &Vector4d<T>::y() const {
    return const_cast<Vector4d*>(this)->y();
}

template <typename T>
const T &Vector4d<T>::z() const {
    return const_cast<Vector4d*>(this)->z();
}

template <typename T>
const T &Vector4d<T>::w() const {
    return const_cast<Vector4d*>(this)->w();
}


template <typename T>
T &Vector4d<T>::x() {
    return Matrix<T>::At(0, 0);
}

template <typename T>
T &Vector4d<T>::y() {
    return Matrix<T>::At(1, 0);
}

template <typename T>
T &Vector4d<T>::z() {
    return Matrix<T>::At(2, 0);
}

template <typename T>
T &Vector4d<T>::w() {
    return Matrix<T>::At(3, 0);
}

template <typename T>
Vector4d<T> &Vector4d<T>::x(T x) {
    SetX(x);
    return *this;
}

template <typename T>
Vector4d<T> &Vector4d<T>::y(T y) {
    SetY(y);
    return *this;
}

template <typename T>
Vector4d<T> &Vector4d<T>::z(T z) {
    SetZ(z);
    return *this;
}

template <typename T>
Vector4d<T> &Vector4d<T>::w(T w) {
    SetW(w);
    return *this;
}


template <typename T>
T Vector4d<T>::Dot(const Vector4d &rhs) const {
    return x()*rhs.x() + y()*rhs.y() + z()*rhs.z() + w()*rhs.w();
}

template <typename T>
T Vector4d<T>::Norm() const {
    return x()*x() + y()*y() + z()*z() + w()*w();
}

template <typename T>
double Vector4d<T>::Length() const {
    return sqrt(Norm());
}

template <typename T>
void Vector4d<T>::Normalize() {
    *this /= Length();
}

template <typename T>
Vector4d<T> Vector4d<T>::Normalized() const {
    Vector4d copy(*this);
    copy.Normalize();

    return copy;
}

template <typename T>
Vector4d<T> Vector4d<T>::Share() const {
    return std::move(Matrix<T>::Share());
}

template <typename T>
Matrix<T> Vector4d<T>::AsMatrix(VectorOrientation orientation) const {
    Matrix<T> result = Matrix<T>::Share();

    if(orientation == kHorizontal)
        result.Transpose();

    return result;
}



#endif // UBURU_RENDERENGINE_VECTOR4D_H