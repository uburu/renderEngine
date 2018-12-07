#ifndef UBURU_RENDERENGINE_MATRIX4X4_H
#define UBURU_RENDERENGINE_MATRIX4X4_H

#include "matrix.h"

template <typename T = double>
class Matrix4x4 : public Matrix<T> {
public:
    static Matrix4x4 Identity(MatrixOrder = MatrixOrder::kRowMajor);
    static Matrix4x4 Zero(MatrixOrder = MatrixOrder::kRowMajor);
    static Matrix4x4 Diagonal(const T &diagonal_elements_value, MatrixOrder = MatrixOrder::kRowMajor);

    Matrix4x4(MatrixOrder = MatrixOrder::kRowMajor);
    Matrix4x4(const T &initial_value, MatrixOrder = MatrixOrder::kRowMajor);
    Matrix4x4(std::initializer_list<std::initializer_list<T>> list, MatrixOrder = MatrixOrder::kRowMajor);
    Matrix4x4(const Matrix<T> &);
    Matrix4x4(Matrix<T> &&);
    Matrix4x4(const Matrix4x4 &) = default;
    Matrix4x4(Matrix4x4 &&) = default;

    Matrix4x4 &operator=(const Matrix4x4 &) = default;
    Matrix4x4 &operator=(Matrix4x4 &&) = default;
    Matrix4x4 &operator=(std::initializer_list<std::initializer_list<T>>);
    void operator*=(const Matrix4x4 &);
    void operator*=(const Matrix<T> &);

    Matrix4x4 operator+(T rhs)                const;
    Matrix4x4 operator-(T rhs)                const;
    Matrix4x4 operator*(T rhs)                const;
    Matrix4x4 operator/(T rhs)                const;
    Matrix4x4 operator+(const Matrix4x4 &rhs) const;
    Matrix4x4 operator-(const Matrix4x4 &rhs) const;

    // WARNING: result order matches with >>this<< matrix (lhs)
    using Matrix<T>::operator*;
    Matrix4x4 operator*(const Matrix4x4 &rhs) const;

    const Matrix4x4 &operator+() const;
    Matrix4x4 operator-() const;

    template <typename U>
    explicit operator Matrix4x4<U>() const;

    template <typename ElementConverter>
    Matrix4x4<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> Map(ElementConverter) const;

private:
    using Matrix<T>::Identity;
    using Matrix<T>::Zero;
    using Matrix<T>::Diagonal;
    using Matrix<T>::Square;
};




/* IMPLEMENTATION */

template <typename T>
Matrix4x4<T> Matrix4x4<T>::Identity(MatrixOrder order) {
    return Diagonal(1, order);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::Zero(MatrixOrder order) {
    return Matrix4x4(0, order);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::Diagonal(const T &value, MatrixOrder order) {
    Matrix4x4 matrix(order);

    matrix.At(0, 0) = value;
    matrix.At(1, 1) = value;
    matrix.At(2, 2) = value;
    matrix.At(3, 3) = value;

    return matrix;
}


template <typename T>
Matrix4x4<T>::Matrix4x4(MatrixOrder order): Matrix<T>(4, 4, order) 
{}

template <typename T>
Matrix4x4<T>::Matrix4x4(const T &initial_value, MatrixOrder order): Matrix<T>(4, 4, initial_value, order) 
{}

template <typename T>
Matrix4x4<T>::Matrix4x4(std::initializer_list<std::initializer_list<T>> list, MatrixOrder order): Matrix<T>(4, 4, order) {
    assert(list.size() == 4 && "Invalid list size for Matrix4x4");
    assert(list.begin()->size() == 4 && "Invalid 1st column size for Matrix4x4");
    assert((list.begin() + 1)->size() == 4 && "Invalid 2nd column size for Matrix4x4");
    assert((list.begin() + 2)->size() == 4 && "Invalid 3rd column size for Matrix4x4");
    assert((list.begin() + 3)->size() == 4 && "Invalid 4th column size for Matrix4x4");

    size_t i = 0, j = 0;
    for(auto &&row : list) {

        j = 0;
        for(auto &&element : row) {
            this->At(i, j) = element;
            ++j;
        }

        ++i;
    }
}

template <typename T>
Matrix4x4<T>::Matrix4x4(const Matrix<T> &other): Matrix<T>(other) {
    assert(other.GetRows() == 4 && other.GetColumns() == 4 && "Invalid size of Matrix4x4");
}

template <typename T>
Matrix4x4<T>::Matrix4x4(Matrix<T> &&other): Matrix<T>(std::move(other)) {
    assert(other.GetRows() == 4 && other.GetColumns() == 4 && "Invalid size of Matrix4x4");
}


template <typename T>
Matrix4x4<T> &Matrix4x4<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
    Matrix4x4 new_matrix(list);
    *this = std::move(new_matrix);

    return *this;
}

template <typename T>
void Matrix4x4<T>::operator*=(const Matrix4x4 &rhs) {
    *this = std::move(*this * rhs);
}

template <typename T>
void Matrix4x4<T>::operator*=(const Matrix<T> &rhs) {
    assert(rhs.GetRows() == 4 && rhs.GetColumns() == 4 && "Can't apply Matrix4x4 *= MatrixUxV where U,V != 4");

    Matrix<T>::operator*=(rhs);
}


template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator+(T rhs) const {
    return Matrix4x4(std::move(*this + rhs));
}

template <typename T>
Matrix4x4<T> operator+(T lhs, const Matrix4x4<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator-(T rhs) const {
    return Matrix4x4(std::move(*this - rhs));
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(T rhs) const {
    return Matrix4x4(std::move(*this * rhs));
}

template <typename T>
Matrix4x4<T> operator*(T lhs, const Matrix4x4<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator/(T rhs) const {
    return Matrix4x4(std::move(*this / rhs));
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4 &rhs) const {
    return Matrix4x4(std::move(*this + rhs));
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4 &rhs) const {
    return Matrix4x4(std::move(*this - rhs));
}


template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4 &rhs) const {
    return Matrix4x4(std::move(Matrix<T>::operator*(rhs)));
}


template <typename T>
const Matrix4x4<T> &Matrix4x4<T>::operator+() const {
    return *this;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator-() const {
    Matrix4x4 copy(*this);
    copy *= -1;

    return copy;
}


template <typename T>
template <typename U>
Matrix4x4<T>::operator Matrix4x4<U>() const {
    return std::move( static_cast<Matrix<U>>(static_cast<Matrix<T>>(*this)));
}


template <typename T>
template <typename ElementConverter>
Matrix4x4<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> Matrix4x4<T>::Map(ElementConverter converter) const {
    return std::move(Matrix<T>::Map(converter));
}



#endif // UBURU_RENDERENGINE_MATRIX4X4_H