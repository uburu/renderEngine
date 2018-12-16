#ifndef UBURU_RENDERENGINE_VECTORUV_H
#define UBURU_RENDERENGINE_VECTORUV_H

#include "vector2d.h"

template <typename T = double>
class VectorUV : public Vector2d<T> {
public:
    using Vector2d<T>::Vector2d;

    template <typename U = T>
    VectorUV<U> Rounded() const;

    template <typename ElementConverter>
    VectorUV<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
    Map(ElementConverter) const;

    T GetU() const;
    T GetV() const;

    void SetU(T);
    void SetV(T);

    const T &u() const;
    const T &v() const;

    T &u();
    T &v();

    VectorUV &u(T);
    VectorUV &v(T);
};




/* IMPLEMENTATION */

template <typename T>
template <typename U>
VectorUV<U> VectorUV<T>::Rounded() const {
    return Map([this](auto &element) {
        if(element < 0) return static_cast<U>(std::ceil(element - 0.5));
        else return static_cast<U>(std::floor(element + 0.5));
    });
}

template <typename T>
template <typename ElementConverter>
VectorUV<std::invoke_result_t<ElementConverter, std::add_lvalue_reference_t<T>>> 
VectorUV<T>::Map(ElementConverter converter) const {
    Vector2d<T>::MatrixSizeAdapter adapter(*this);
    return std::move(Matrix<T>::Map(converter));
}


template <typename T>
T VectorUV<T>::GetU() const {
    return this->x();
}

template <typename T>
T VectorUV<T>::GetV() const {
    return this->y();
}


template <typename T>
void VectorUV<T>::SetU(T u) {
    this->SetX(u);
}

template <typename T>
void VectorUV<T>::SetV(T v) {
    this->SetY(v);
}


template <typename T>
const T &VectorUV<T>::u() const {
    return this->x();
}

template <typename T>
const T &VectorUV<T>::v() const {
    return this->y();
}


template <typename T>
T &VectorUV<T>::u() {
    return this->x();
}

template <typename T>
T &VectorUV<T>::v() {
    return this->y();
}


template <typename T>
VectorUV<T> &VectorUV<T>::u(T u) {
    SetU(u);
    return *this;
}

template <typename T>
VectorUV<T> &VectorUV<T>::v(T v) {
    SetV(v);
    return *this;
}


#endif // UBURU_RENDERENGINE_VECTORUV_H