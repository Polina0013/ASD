// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include <cmath>     // для std::abs
#include <type_traits> // для std::is_floating_point

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

    // Functions //
    MathVector<T> add(const MathVector<T>&) const;
    MathVector<T> sub(const MathVector<T>&) const;
    MathVector<T> mult_by_number(const T&) const;
    MathVector<T> div_by_number(const T&) const;
    T scalar_mult(const MathVector<T>&) const;

    // Operators //
    using TVector<T>::operator[];
    
    MathVector<T> operator+(const MathVector<T>&) const;
    MathVector<T> operator-(const MathVector<T>&) const;
    MathVector<T> operator*(const T&) const;
    MathVector<T> operator/(const T&) const;
    T operator*(const MathVector<T>&) const;

    MathVector<T>& operator+=(const MathVector<T>&);
    MathVector<T>& operator-=(const MathVector<T>&);
    MathVector<T>& operator*=(const T&);
    MathVector<T>& operator/=(const T&);

    bool operator==(const MathVector<T>&) const;
    bool operator!=(const MathVector<T>&) const;

};

// Constructors //
template<class T>
MathVector<T>::MathVector() : TVector<T>() {}

template<class T>
MathVector<T>::MathVector(int size) : TVector<T>(size) {}

template<class T>
MathVector<T>::MathVector(int size, const T* data) : TVector<T>(size, data) {}

template<class T>
MathVector<T>::MathVector(std::initializer_list<T> init) : TVector<T>(init) {}

template<class T>
MathVector<T>::MathVector(const MathVector<T>& other) : TVector<T>(other) {}

// Destructor //
template<class T>
MathVector<T>::~MathVector() {}

// Functions //
template<class T>
MathVector<T> MathVector<T>::add(const MathVector<T>& other) const {
    if (this->size() != other.size()) throw std::logic_error("The dimensions of the vectors do not match!");

    MathVector<T> result(this->size());

    for (int i = 0; i < this->size(); i++) {
        result.data()[i] = this->data()[i] + other.data()[i];
    }
    return result;
}

template<class T>
MathVector<T> MathVector<T>::sub(const MathVector<T>& other) const {
    if (this->size() != other.size()) throw std::logic_error("The dimensions of the vectors do not match!");

    MathVector<T> result(this->size());

    for (int i = 0; i < this->size(); i++) {
        result.data()[i] = this->data()[i] - other.data()[i];
    }
    return result;
}

template<class T>
MathVector<T> MathVector<T>::mult_by_number(const T& other) const {
    MathVector<T> result(this->size());

    for (int i = 0; i < this->size(); i++) {
        result.data()[i] = this->data()[i] * other;
    }
    return result;
}

template<class T>
MathVector<T> MathVector<T>::div_by_number(const T& other) const {
    if (other == T()) throw std::logic_error("Division by zero!");
    
    MathVector<T> result(this->size());

    for (int i = 0; i < this->size(); i++) {
        result.data()[i] = this->data()[i] / other;
    }
    return result;
}

template<class T>
T MathVector<T>::scalar_mult(const MathVector<T>& other) const {
    if (this->size() != other.size()) throw std::logic_error("The dimensions of the vectors do not match!");

    T result = T();

    for (int i = 0; i < this->size(); i++) {
        result += this->data()[i] * other.data()[i];
    }
    return result;
}

// Operators //
template<class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
    return this->add(other);
}

template<class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
    return this->sub(other);
}

template<class T>
MathVector<T> MathVector<T>::operator*(const T& other) const {
    return this->mult_by_number(other);
}

template<class T>
MathVector<T> MathVector<T>::operator/(const T& other) const {
    return this->div_by_number(other);
}

template<class T>
T MathVector<T>::operator*(const MathVector<T>& other) const {
    return this->scalar_mult(other);
}

template<class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
    *this = *this + other;
    return *this;
}

template<class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other) {
    *this = *this - other;
    return *this;
}

template<class T>
MathVector<T>& MathVector<T>::operator*=(const T& other) {
    *this = *this * other;
    return *this;
}

template<class T>
MathVector<T>& MathVector<T>::operator/=(const T& other) {
    *this = *this / other;
    return *this;
}

template<class T>
bool MathVector<T>::operator==(const MathVector<T>& other) const {
    if (this->size() != other.size()) return false;

    if (this->size() == 0) return true;

    // Сравнение для чисел float
    if constexpr (std::is_floating_point<T>::value) {
        T eps = static_cast<T>(1e-6); // погрешность
        for (int i = 0; i < this->size(); ++i) {
            if (std::abs((*this)[i] - other[i]) > eps)
                return false;
        }
        return true;
    }

    else {
        for (int i = 0; i < this->size(); ++i) {
            if ((*this)[i] != other[i]) return false;
        }
        return true;
    }
}

template<class T>
bool MathVector<T>::operator!=(const MathVector<T>& other) const {
    return !(*this == other);
}