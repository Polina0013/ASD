// Õ≈ –≈¿À»«Œ¬¿ÕŒ
// Copyright 2025 Pozdnova Polina
#pragma once

#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#include <stdexcept>


#include "..\lib_mathvector\mathvector.h"

template<class T>
class Matrix : public MathVector<T> {
public:
    // Constructors //
    Matrix();
    explicit Matrix(int, int);
    Matrix(const MathVector<MathVector<T>>&);
    Matrix(const Matrix<T>&);

    // Destructor //
    ~Matrix();

    Matrix<T> add(const Matrix<T>&);
    Matrix<T> sub(const Matrix<T>&);
    Matrix<T> mult(const Matrix<T>&);
    Matrix<T> transpose();

    // Operators //
    Matrix<T> operator+(const Matrix<T>&) const;
    Matrix<T> operator-(const Matrix<T>&) const;
    Matrix<T> operator*(const Matrix<T>&) const;

    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
    Matrix<T>& operator*=(const Matrix<T>&);

    bool operator==(const Matrix<T>&) const;
    bool operator!=(const Matrix<T>&) const;

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);
    friend std::istream& operator>>(std::istream& in, Matrix<T>& matrix);
};

// Constructors //
template<class T>
Matrix<T>::Matrix() {

}

template<class T>
Matrix<T>::Matrix(int M, int N) {

}

template<class T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>&) {

}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other) {

}

// Destructor //
template<class T>
Matrix<T>::~Matrix() {

}

template<class T>
Matrix<T> Matrix<T>::add(const Matrix<T>& other) {}
template<class T>
Matrix<T> Matrix<T>::sub(const Matrix<T>& other) {}
template<class T>
Matrix<T> Matrix<T>::mult(const Matrix<T>& other) {}
template<class T>
Matrix<T> Matrix<T>::transpose() {}

// Operators //
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>&) const {}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>&) const {}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>&) const {}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>&) {}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>&) {}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>&) {}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>&) const {}

template<class T>
bool Matrix<T>::operator!=(const Matrix<T>&) const {}

template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {}

template<class T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {}