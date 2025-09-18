// НЕ РЕАЛИЗОВАНО
// Математический вектор. Сложение, умножение, вычитание векторов 
// Copyright 2025 Pozdnova Polina
#pragma once

#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#include <stdexcept>

#include "..\lib_tvector\tvector.h"

template<class T>
class MathVector : public TVector<T> {

public:
    // Constructors //
    MathVector();
    explicit MathVector(int);
    MathVector(int, const T*);
    explicit MathVector(std::initializer_list<T>);
    MathVector(const MathVector<T>&);

    // Destructor //
    ~MathVector();

    MathVector<T> add(MathVector<T>&);
    MathVector<T> sub(MathVector<T>&);
    MathVector<T> mult(MathVector<T>&);

    // Operators //
    T& operator[](int index);

    MathVector<T> operator+(const MathVector<T>&) const;
    MathVector<T> operator-(const MathVector<T>&) const;
    MathVector<T> operator*(const MathVector<T>&) const;

    MathVector<T>& operator+=(const MathVector<T>&);
    MathVector<T>& operator-=(const MathVector<T>&);
    MathVector<T>& operator*=(const MathVector<T>&);

    bool operator==(const MathVector<T>&) const;
    bool operator!=(const MathVector<T>&) const;
};

// Constructors //
template<class T>
MathVector<T>::MathVector() {

}

template<class T>
MathVector<T>::MathVector(int size) {

}

template<class T>
MathVector<T>::MathVector(int size, const T* data) {

}

template<class T>
MathVector<T>::MathVector(std::initializer_list<T> init) {

}

template<class T>
MathVector<T>::MathVector(const MathVector<T>& other) {

}

// Destructor //
template<class T>
MathVector<T>::~MathVector() {

}

template<class T>
MathVector<T> MathVector<T>::add(MathVector<T>& other) {}
template<class T>
MathVector<T> MathVector<T>::sub(MathVector<T>& other) {}
template<class T>
MathVector<T> MathVector<T>::mult(MathVector<T>& other) {}

// Operators //
template<class T>
T& MathVector<T>::operator[](int index) {}

template<class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>&) const {}

template<class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>&) const {}

template<class T>
MathVector<T> MathVector<T>::operator*(const MathVector<T>&) const {}

template<class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>&) {}

template<class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>&) {}

template<class T>
MathVector<T>& MathVector<T>::operator*=(const MathVector<T>&) {}

template<class T>
bool MathVector<T>::operator==(const MathVector<T>&) const {}

template<class T>
bool MathVector<T>::operator!=(const MathVector<T>&) const {}