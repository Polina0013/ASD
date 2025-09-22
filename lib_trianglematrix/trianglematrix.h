// Õ≈ –≈¿À»«Œ¬¿ÕŒ
// Copyright 2025 Pozdnova Polina
#pragma once

#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#include <stdexcept>


#include "..\lib_matrix\matrix.h"

template<class T>
class TriangleMatrix : public Matrix<T> {
public:
    // Constructors //
    TriangleMatrix();
    explicit TriangleMatrix(int);
    TriangleMatrix(const MathVector<MathVector<T>>&);
    TriangleMatrix(const TriangleMatrix<T>&);

    // Destructor //
    ~TriangleMatrix();

    TriangleMatrix<T> add(const TriangleMatrix<T>&);
    TriangleMatrix<T> sub(const TriangleMatrix<T>&);
    TriangleMatrix<T> mult(const TriangleMatrix<T>&);
    TriangleMatrix<T> transpose();

    // Operators //
    TriangleMatrix<T> operator+(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator-(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator*(const TriangleMatrix<T>&) const;

    TriangleMatrix<T>& operator+=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator-=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator*=(const TriangleMatrix<T>&);

    bool operator==(const TriangleMatrix<T>&) const;
    bool operator!=(const TriangleMatrix<T>&) const;

    friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix);
    friend std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matrix);
};

// Constructors //
template<class T>
TriangleMatrix<T>::TriangleMatrix() {

}

template<class T>
TriangleMatrix<T>::TriangleMatrix(int M) {

}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const MathVector<MathVector<T>>&) {

}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) {

}

// Destructor //
template<class T>
TriangleMatrix<T>::~TriangleMatrix() {

}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::add(const TriangleMatrix<T>& other) {}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::sub(const TriangleMatrix<T>& other) {}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::mult(const TriangleMatrix<T>& other) {}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::transpose() {}

// Operators //
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>&) const {}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>&) const {}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>&) const {}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>&) {}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>&) {}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const TriangleMatrix<T>&) {}

template<class T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>&) const {}

template<class T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>&) const {}

template<class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {}

template<class T>
std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matrix) {}