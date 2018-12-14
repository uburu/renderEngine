#ifndef UBURU_RENDERENGINE_COLOR_H
#define UBURU_RENDERENGINE_COLOR_H

#include "vector4d.h"

template <typename T = unsigned char>
class Color : public Vector4d<T> {
public:
    using Vector4d<T>::Vector4d;

    T GetRed() const;
    T GetGreen() const;
    T GetBlue() const;
    T GetAlpha() const;

    void GetRed(T);
    void GetGreen(T);
    void GetBlue(T);
    void GetAlpha(T);

    const T &r() const;
    const T &g() const;
    const T &b() const;
    const T &a() const;

    T &r();
    T &g();
    T &b();
    T &a();

    Color &r(T);
    Color &g(T);
    Color &b(T);
    Color &a(T);
};




/* IMPLEMENTATION */

template <typename T>
T Color<T>::GetRed() const {
    return x();
}

template <typename T>
T Color<T>::GetGreen() const {
    return y();    
}

template <typename T>
T Color<T>::GetBlue() const {
    return z();
}

template <typename T>
T Color<T>::GetAlpha() const {
    return w();
}


template <typename T>
void Color<T>::GetRed(T r) {
    SetX(r);
}

template <typename T>
void Color<T>::GetGreen(T g) {
    SetY(g);
}

template <typename T>
void Color<T>::GetBlue(T b) {
    SetZ(b);
}

template <typename T>
void Color<T>::GetAlpha(T a) {
    SetW(a);
}


template <typename T>
const T &Color<T>::r() const {
    return x();
}

template <typename T>
const T &Color<T>::g() const {
    return y();
}

template <typename T>
const T &Color<T>::b() const {
    return z();
}

template <typename T>
const T &Color<T>::a() const {
    return w();
}


template <typename T>
T &Color<T>::r() {
    return x();
}

template <typename T>
T &Color<T>::g() {
    return y();
}

template <typename T>
T &Color<T>::b() {
    return z();
}

template <typename T>
T &Color<T>::a() {
    return w();
}


template <typename T>
Color<T> &Color<T>::r(T r) {
    SetX(r);
    return *this;
}

template <typename T>
Color<T> &Color<T>::g(T g) {
    SetY(g);
    return *this;
}

template <typename T>
Color<T> &Color<T>::b(T b) {
    SetZ(b);
    return *this;
}

template <typename T>
Color<T> &Color<T>::a(T a) {
    SetW(a);
    return *this;
}


#endif // UBURU_RENDERENGINE_COLOR_H