// Uburu Render Engine
// File: Matrix.h
// Author: Daniel Shiposha
// Copyright (c) Uburu

#ifndef UBURU_RENDERENGINE_MATRIX_H
#define UBURU_RENDERENGINE_MATRIX_H

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <cmath>
#include <atomic>
#include <iostream>

#include <pstl/algorithm>
#include <pstl/execution>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>

#ifndef UU_MATRIX_ROW_GRAINSIZE
#   define UU_MATRIX_ROW_GRAINSIZE 16
#endif // UU_MATRIX_ROW_GRAINSIZE 

#ifndef UU_MATRIX_COLUMN_GRAINSIZE
#   define UU_MATRIX_COLUMN_GRAINSIZE 16
#endif // UU_MATRIX_COLUMN_GRAINSIZE 

namespace detail {
    template <size_t D, typename T>
    class MatrixSizeAdapter;
}

enum class MatrixOrder {
    kRowMajor,
    kColumnMajor
};

template <typename T = double>
class Matrix {
public:
    static Matrix Identity(size_t size,             MatrixOrder = MatrixOrder::kRowMajor);
    static Matrix Zero(size_t rows, size_t columns, MatrixOrder = MatrixOrder::kRowMajor);

    static Matrix Diagonal(size_t size, const T &diagonal_elements_value, MatrixOrder = MatrixOrder::kRowMajor);

    static Matrix Square(size_t size,                           MatrixOrder = MatrixOrder::kRowMajor);
    static Matrix Square(size_t size, const T &elements_values, MatrixOrder = MatrixOrder::kRowMajor);

    Matrix(size_t rows, size_t columns,                          MatrixOrder = MatrixOrder::kRowMajor);
    Matrix(size_t rows, size_t columns, const T &initial_value,  MatrixOrder = MatrixOrder::kRowMajor);
    Matrix(std::initializer_list<std::initializer_list<T>> list, MatrixOrder = MatrixOrder::kRowMajor);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other);
    virtual ~Matrix();

    Matrix &operator=(const Matrix &rhs);
    Matrix &operator=(Matrix &&rhs);
    Matrix &operator=(std::initializer_list<std::initializer_list<T>>);
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);


    void operator+=(const Matrix &rhs);
    void operator-=(const Matrix &rhs);
    
    // WARNING: be careful with that operator! Implicitly size changing is not allowed!
    // e.g. A = A*B
    // It can be overwritten as A *= B only if (A.GetRows() == (A*B).GetRows() && A.GetColumns() == (A*B).GetColumns()) is true
    void operator*=(const Matrix &rhs);


    Matrix operator+(T rhs)             const;
    Matrix operator-(T rhs)             const;
    Matrix operator*(T rhs)             const;
    Matrix operator/(T rhs)             const;
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;

    // WARNING: result order matches with >>this<< matrix (lhs)
    Matrix operator*(const Matrix &rhs) const;

    const Matrix &operator+() const;
    Matrix operator-() const;

    template <typename U>
    explicit operator Matrix<U>() const; 

    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;

    template <typename ElementConverter>
    Matrix<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> Map(ElementConverter) const;

    size_t GetRows()    const;
    size_t GetColumns() const;

    MatrixOrder GetOrder() const;
    void SetOrder(MatrixOrder);

    Matrix WithOrder(MatrixOrder) const;

    const T &At(size_t i, size_t j) const;
    T &At(size_t i, size_t j);

    void Round();
    Matrix Rounded() const;

    void Transpose();
    Matrix Transposed() const;

    Matrix Share() const;

    const T *RawData() const;
    T *RawData();

    T *begin();
    T *end();

    std::reverse_iterator<T*> rbegin();
    std::reverse_iterator<T*> rend();
    
    const T *cbegin() const;
    const T *cend() const;

    std::reverse_iterator<const T*> crbegin() const;
    std::reverse_iterator<const T*> crend() const;

#ifndef UU_DISABLE_PARALLEL_MATRIX
    size_t GetRowGrainsize() const;
    size_t GetColumnGrainsize() const;

    void SetRowGrainsize(size_t);
    void SetColumnGrainsize(size_t);
#endif // UU_DISABLE_PARALLEL_MATRIX

protected:
    template <typename U>
    friend class Matrix;

    template <size_t D, typename U>
    friend class detail::MatrixSizeAdapter;

    Matrix(size_t rows, size_t columns, size_t data_size, std::shared_ptr<T> elements, MatrixOrder order, bool is_transposed);

    size_t               rows, columns;
    size_t               data_size;
    std::shared_ptr<T>   elements;
    MatrixOrder          order;
    bool                 is_transposed;

#ifndef UU_DISABLE_PARALLEL_MATRIX
    size_t row_grainsize    = UU_MATRIX_ROW_GRAINSIZE;
    size_t column_grainsize = UU_MATRIX_COLUMN_GRAINSIZE;
#endif // UU_DISABLE_PARALLEL_MATRIX
};



/* IMPLEMENTATION */

template <typename T>
Matrix<T> Matrix<T>::Identity(size_t size, MatrixOrder order) {
    return Diagonal(size, 1, order);
}

template <typename T>
Matrix<T> Matrix<T>::Zero(size_t rows, size_t columns, MatrixOrder order) {
    return Matrix(rows, columns, 0, order);
}

template <typename T>
Matrix<T> Matrix<T>::Diagonal(size_t size, const T &value, MatrixOrder order) {
    auto matrix = Square(size, order);

    for(size_t i = 0; i < size; ++i) matrix.At(i, i) = value;
    return matrix;
}


template <typename T>
Matrix<T> Matrix<T>::Square(size_t size, MatrixOrder order) {
    return Matrix(size, size, order);
}

template <typename T>
Matrix<T> Matrix<T>::Square(size_t size, const T &value, MatrixOrder order) {
    return Matrix(size, size, value, order);
}


template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, MatrixOrder order)
: Matrix(rows, columns, 0, order) {
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T &initial_value, MatrixOrder order)
: rows(rows), 
columns(columns), 
data_size(rows*columns), 
elements(new T[data_size], std::default_delete<T[]>()), 
order(order), 
is_transposed(false) {
    assert(rows > 0 && columns > 0 && "Zero size matrix");

    std::fill(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        initial_value
    );
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list, MatrixOrder order)
: rows(0), 
columns(0), 
data_size(0), 
elements(nullptr), 
order(order), 
is_transposed(false) {
    assert(list.size() > 0 && "Empty matrix list");
    assert(list.begin()->size() > 0 && "Empty matrix row list");

    rows      = list.size();
    columns   = list.begin()->size();
    data_size = rows*columns;
    elements.reset(new T[data_size], std::default_delete<T[]>());

    size_t i = 0, j = 0;
    for(auto &&row : list) {
        assert(row.size() == columns && "Ambiguous matrix row list ");

        j = 0;
        for(auto &&element : row) {
            At(i, j) = element;
            ++j;
        } 

        ++i;
    }   
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, size_t data_size, std::shared_ptr<T> elements, MatrixOrder order, bool is_transposed)
: rows(rows), columns(columns), data_size(data_size), elements(elements), order(order), is_transposed(is_transposed) {}

template <typename T>
Matrix<T>::Matrix(const Matrix &other)
: rows(other.rows), 
columns(other.columns), 
data_size(other.data_size), 
elements(new T[data_size], std::default_delete<T[]>()), 
order(other.order), 
is_transposed(other.is_transposed) {
    std::copy(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        other.cbegin(),
        other.cend(),
        begin()
    );
}

template <typename T>
Matrix<T>::Matrix(Matrix &&other)
: rows(other.rows),
columns(other.columns),
data_size(other.data_size),
elements(std::move(other.elements)),
order(other.order),
is_transposed(other.is_transposed)
{}

template <typename T>
Matrix<T>::~Matrix() {

}


template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &rhs) {
    if(this != &rhs) {
        Matrix copy(rhs);
        *this = std::move(copy);
    }

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&rhs) {
    rows          = rhs.rows;
    columns       = rhs.columns;
    data_size     = rhs.data_size;
    elements      = std::move(rhs.elements);
    order         = rhs.order;
    is_transposed = rhs.is_transposed;

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
    Matrix new_matrix(list);
    *this = std::move(new_matrix);
    return *this;
}

template <typename T>
void Matrix<T>::operator+=(T rhs) {
    std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        begin(),
        [&rhs](auto &element) { return element + rhs; }
    );
}

template <typename T>
void Matrix<T>::operator-=(T rhs) {
    std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        begin(),
        [&rhs](auto &element) { return element - rhs; }
    );
}

template <typename T>
void Matrix<T>::operator*=(T rhs) {
std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        begin(),
        [&rhs](auto &element) { return element * rhs; }
    );
}

template <typename T>
void Matrix<T>::operator/=(T rhs) {
    std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        begin(),
        [&rhs](auto &element) { return element / rhs; }
    );
}



template <typename T>
void Matrix<T>::operator+=(const Matrix &rhs) {
    std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        rhs.cbegin(),
        begin(),
        std::plus<T>()
    );
}

template <typename T>
void Matrix<T>::operator-=(const Matrix &rhs) {
std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        rhs.cbegin(),
        begin(),
        std::minus<T>()
    );
}


// WARNING: be careful with that operator! Implicitly size changing is not allowed!
// e.g. A = A*B
// It can be overwritten as A *= B only if (A.GetRows() == (A*B).GetRows() && A.GetColumns() == (A*B).GetColumns()) is true
template <typename T>
void Matrix<T>::operator*=(const Matrix &rhs) {
    assert(columns == rhs.columns && "Implicit size changing is not allowed");

    *this = std::move(*this * rhs);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(T rhs) const {
    Matrix copy(*this);
    copy += rhs;

    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(T rhs) const {
    Matrix copy(*this);
    copy -= rhs;

    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T rhs) const {
    Matrix copy(*this);
    copy *= rhs;

    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T rhs) const {
    Matrix copy(*this);
    copy /= rhs;

    return copy;
}

template <typename T>
Matrix<T> operator+(T lhs, const Matrix<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
Matrix<T> operator*(T lhs, const Matrix<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &rhs) const {
    Matrix copy(*this);
    copy += rhs;

    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &rhs) const {
    Matrix copy(*this);
    copy -= rhs;

    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &rhs) const {
    assert(columns == rhs.rows && "Matrix multiplication sizes mismatch");

    auto result = Zero(rows, rhs.columns, order);

#if defined(UU_DISABLE_PARALLEL_MATRIX)
    size_t i = 0, j = 0, k = 0;

    // TODO: Use Strassen algorithm
    size_t rows_end = GetRows();
    size_t rhs_columns_end = rhs.GetColumns();
    size_t columns_end = GetColumns();
	for(i = 0; i < rows_end; ++i) {
		for(j = 0; j < rhs_columns_end; ++j) {
			for(k = 0; k < columns_end; ++k) {
				result.At(i, j) += At(i, k) * rhs.At(k, j);
			}
		}
	}
#else
    parallel_for(
        tbb::blocked_range2d<size_t>(0, GetRows(), GetRowGrainsize(), 0, rhs.GetColumns(), rhs.GetColumnGrainsize()),
        [&](const tbb::blocked_range2d<size_t>& range) {
            size_t i = 0, j = 0, k = 0;

            size_t rows_begin = range.rows().begin();
            size_t rows_end = range.rows().end();

            size_t rhs_columns_begin = range.cols().begin();  
            size_t rhs_columns_end = range.cols().end();

            size_t columns_end = GetColumns();

            for(i = rows_begin; i != rows_end; ++i) {
                for(j = rhs_columns_begin; j != rhs_columns_end; ++j) {
                    for(k = 0; k < columns_end; ++k)
                        result.At(i, j) += At(i, k) * rhs.At(k, j);
                }
            }
        }     
    );
#endif // UU_DISABLE_PARALLEL_MATRIX

    return result;
}

template <typename T>
const Matrix<T> &Matrix<T>::operator+() const {
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix copy(*this);
    copy *= -1;

    return copy;
}

template <typename T>
template <typename U>
Matrix<T>::operator Matrix<U>() const {
    static_assert(std::is_convertible_v<T, U>, "Matrix: apply cast operator (source type isn't convertible to target type)");

    return Map([](auto &original) {
        return static_cast<U>(original);
    });
} 

template <typename T>
bool Matrix<T>::operator==(const Matrix &rhs) const {
    if(GetRows() != rhs.GetRows() || GetColumns() != rhs.GetColumns()) return false;
    if(elements == rhs.elements) return true;

#if defined(UU_DISABLE_PARALLEL_MATRIX)
    size_t rows_end = GetRows();
    size_t columns_end = GetColumns();
    for(size_t i = 0, j = 0; i < rows_end; ++i) {
        for(j = 0; j < columns_end; ++j) {
            if(At(i, j) != rhs.At(i, j)) return false;
        }
    }

    return true;
#else
    std::atomic_bool result(true);

    parallel_for(
        tbb::blocked_range2d<size_t>(0, GetRows(), GetRowGrainsize(), 0, GetColumns(), GetColumnGrainsize()),
        [&](const tbb::blocked_range2d<size_t>& range) {
            size_t rows_begin = range.rows().begin();
            size_t rows_end = range.rows().end();
            size_t columns_begin = range.cols().begin();
            size_t columns_end = range.cols().end();

            for(size_t i = rows_begin, j = columns_begin && result; i < rows_end; ++i) {
                for(j = columns_begin; j < columns_end && result; ++j) {
                    if(At(i, j) != rhs.At(i, j)) result = false;
                }
            }
        }     
    );

    return result;
#endif // UU_DISABLE_PARALLEL_MATRIX
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix &rhs) const {
    return !(*this == rhs);
}

template <typename T>
template <typename ElementConverter>
Matrix<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> Matrix<T>::Map(ElementConverter converter) const {
    Matrix<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> result(rows, columns, order);
    result.is_transposed = is_transposed;

    std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        cbegin(),
        cend(),
        result.begin(),
        converter
    );

    return result;
}

template <typename T>
size_t Matrix<T>::GetRows() const {
    if(!is_transposed) return rows;
    else return columns;
}

template <typename T>
size_t Matrix<T>::GetColumns() const {
    if(!is_transposed) return columns;
    else return rows;
}

template <typename T>
MatrixOrder Matrix<T>::GetOrder() const {
    return order;
}

template <typename T>
void Matrix<T>::SetOrder(MatrixOrder order) {
    *this = std::move(WithOrder(order));
}

template <typename T>
Matrix<T> Matrix<T>::WithOrder(MatrixOrder order) const {
    if(order == this->order) return *this;    

    Matrix result(rows, columns, order);

#if defined(UU_DISABLE_PARALLEL_MATRIX)
    size_t rows_end = GetRows();
    size_t columns_end = GetColumns();
    for(size_t i = 0, j = 0; i < rows_end; ++i) {
        for(j = 0; j < columns_end; ++j) {
            result.At(i, j) = At(i, j);
        }
    }
#else
    parallel_for(
        tbb::blocked_range2d<size_t>(0, GetRows(), GetRowGrainsize(), 0, GetColumns(), GetColumnGrainsize()),
        [&](const tbb::blocked_range2d<size_t>& range) {
            size_t rows_begin = range.rows().begin();
            size_t rows_end = range.rows().end();
            size_t columns_begin = range.cols().begin();
            size_t columns_end = range.cols().end();

            for(size_t i = rows_begin, j = columns_begin; i < rows_end; ++i) {
                for(j = columns_begin; j < columns_end; ++j) {
                    result.At(i, j) = At(i, j);
                }
            }
        }     
    );
#endif // UU_DISABLE_PARALLEL_MATRIX

    return result;
}

template <typename T>
const T &Matrix<T>::At(size_t i, size_t j) const {
    return const_cast<Matrix*>(this)->At(i, j);
}

template <typename T>
T &Matrix<T>::At(size_t i, size_t j) {
    assert(i < GetRows() && j < GetColumns() && "Invalid matrix indices");

    if(is_transposed) std::swap(i, j);

    if(order == MatrixOrder::kRowMajor) return elements.get()[columns*i + j];
    else return elements.get()[rows*j + i];
}

template <typename T>
void Matrix<T>::Round() {
    std::transform(
#ifndef UU_DISABLE_PARALLEL_MATRIX 
        pstl::execution::par, 
#endif // UU_DISABLE_PARALLEL_MATRIX
        begin(),
        end(),
        begin(),
        [](auto &element) {
            if(element < 0) return std::ceil(element - 0.5);
            else return std::floor(element + 0.5);
        }
    );
}

template <typename T>
Matrix<T> Matrix<T>::Rounded() const {
    Matrix copy(*this);
    copy.Round();

    return copy;
}

template <typename T>
void Matrix<T>::Transpose() {
    is_transposed = !is_transposed;
}

template <typename T>
Matrix<T> Matrix<T>::Transposed() const {
    Matrix copy(*this);
    copy.Transpose();

    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::Share() const {
    return Matrix(rows, columns, data_size, elements, order, is_transposed);
}

template <typename T>
const T *Matrix<T>::RawData() const {
    return const_cast<Matrix*>(this)->RawData();
}

template <typename T>
T *Matrix<T>::RawData() {
    return elements.get();
}

template <typename T>
T *Matrix<T>::begin() {
    return elements.get();
}

template <typename T>
T *Matrix<T>::end() {
    return elements.get() + data_size;
}

template <typename T>
std::reverse_iterator<T*> Matrix<T>::rbegin() {
    return std::reverse_iterator<T*>(end());
}

template <typename T>
std::reverse_iterator<T*> Matrix<T>::rend() {
    return std::reverse_iterator<T*>(begin());
}

template <typename T>
const T *Matrix<T>::cbegin() const {
    return const_cast<Matrix*>(this)->begin();
}

template <typename T>
const T *Matrix<T>::cend() const {
    return const_cast<Matrix*>(this)->end();
}

template <typename T>
std::reverse_iterator<const T*> Matrix<T>::crbegin() const {
    return const_cast<Matrix*>(this)->rbegin();
}

template <typename T>
std::reverse_iterator<const T*> Matrix<T>::crend() const {
    return const_cast<Matrix*>(this)->rend();
}

#ifndef UU_DISABLE_PARALLEL_MATRIX
template <typename T>
size_t Matrix<T>::GetRowGrainsize() const {
    return row_grainsize;
}

template <typename T>
size_t Matrix<T>::GetColumnGrainsize() const {
    return column_grainsize;
}

template <typename T>
void Matrix<T>::SetRowGrainsize(size_t grainsize) {
    row_grainsize = grainsize;
}

template <typename T>
void Matrix<T>::SetColumnGrainsize(size_t grainsize) {
    column_grainsize = grainsize;
}
#endif // UU_DISABLE_PARALLEL_MATRIX

template <typename T>
std::ostream &operator<<(std::ostream &lhs, const Matrix<T> &rhs) {
    size_t rows = rhs.GetRows(), columns = rhs.GetColumns();

    for(size_t i = 0, j = 0; i < rows; ++i) {

        lhs << "{ ";

        for(j = 0; j < columns; ++j) lhs << rhs.At(i, j) << ' ';

        lhs << '}' << std::endl;
    }

    return lhs;
}

#endif // UBURU_RENDERENGINE_MATRIX_H