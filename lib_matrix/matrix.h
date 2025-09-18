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