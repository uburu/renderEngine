#ifndef UBURU_RENDERENGINE_VECTORUV_H
#define UBURU_RENDERENGINE_VECTORUV_H

#include "vector2d.h"

template <typename T = double>
class VectorUV : public Vector2d<T> {
public:
    using Vector2d<T>::Vector2d;

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