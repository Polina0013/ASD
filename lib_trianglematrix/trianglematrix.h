// Copyright 2025 Pozdnova Polina

#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include "..\lib_matrix\matrix.h"

enum class TriangleType {
    Upper,
    Lower
};

template<class T>
class TriangleMatrix : public Matrix<T> {
protected:
    TriangleType _type;
public:
    // Constructors //
    TriangleMatrix();
    explicit TriangleMatrix(int, TriangleType);
    TriangleMatrix(const MathVector<MathVector<T>>&, TriangleType);
    TriangleMatrix(std::initializer_list<std::initializer_list<T>>, TriangleType);
    TriangleMatrix(const TriangleMatrix<T>&);

    // Destructor //
    ~TriangleMatrix();

    TriangleMatrix<T> add(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> sub(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> mult(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> mult_by_number(const T&) const;
    TriangleMatrix<T> div_by_number(const T&) const;
    TriangleMatrix<T> transpose() const;

    // Operators //
    TriangleMatrix<T> operator+(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator-(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator*(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator*(const T&) const;
    TriangleMatrix<T> operator/(const T&) const;

    TriangleMatrix<T>& operator+=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator-=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator*=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator*=(const T&);
    TriangleMatrix<T>& operator/=(const T&);

    bool operator==(const TriangleMatrix<T>&) const;
    bool operator!=(const TriangleMatrix<T>&) const;

    friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix);
    friend std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matrix);

    MathVector<T>& operator[](int index);
    const MathVector<T>& operator[](int index) const;

    T& TriangleMatrix<T>::operator()(int i, int j);
    const T& TriangleMatrix<T>::operator()(int i, int j) const;
};

// Constructors //
template<class T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>(), _type(TriangleType::Upper) {}

template<class T>
TriangleMatrix<T>::TriangleMatrix(int size, TriangleType t) : Matrix<T>(size, size), _type(t) {
    for (int i = 0; i < size; ++i) {
        if (t == TriangleType::Upper)
            (*this)[i] = MathVector<T>(size - i);
        else
            (*this)[i] = MathVector<T>(i + 1);
    }
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const MathVector<MathVector<T>>& other, TriangleType t) : Matrix<T>(other.size(), other.size()) {
    if (other.size() == 0) throw std::logic_error("Matrix cannot be empty!");

    this->_rows = other.size();
    this->_columns = other.size();
    this->_type = t;

    this->resize(this->_rows);

    if (t == TriangleType::Upper) {
        for (int i = 0; i < this->_rows; ++i) {
            int expected_size = this->_columns - i;
            if (other[i].size() != expected_size) throw std::logic_error("Invalid row length for upper triangular matrix!");

            (*this)[i] = other[i];
        }
    }
    else {
        for (int i = 0; i < this->_rows; ++i) {
            int expected_size = i + 1;
            if (other[i].size() != expected_size) throw std::logic_error("Invalid row length for lower triangular matrix!");

            (*this)[i] = other[i];
        }
    }
}


template<class T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> other, TriangleType t) : _type(t) {
    this->_rows = static_cast<int>(other.size());
    this->_columns = this->_rows;

    this->clear();

    int i = 0;
    for (const auto& row : other) {
        this->push_back(MathVector<T>(row));
        i++;
    }

    // Проверка на корректность ввода
    if (_type == TriangleType::Upper) {
        for (int i = 0; i < this->_rows; i++) {
            int expected_size = this->_columns - i;
            if ((*this)[i].size() != expected_size) throw std::logic_error("Invalid row length for upper triangular matrix!");
        }
    }
    else {
        for (int i = 0; i < this->_rows; i++) {
            int expected_size = i + 1;
            if ((*this)[i].size() != expected_size) throw std::logic_error("Invalid row length for lower triangular matrix!");
        }
    }
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other), _type(other._type) {}

// Destructor //
template<class T>
TriangleMatrix<T>::~TriangleMatrix() {}

// Functions //
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::add(const TriangleMatrix<T>& other) const {
    if (this->_rows != other._rows || this->_type != other._type) throw std::logic_error("Triangle matrices are not compatible for addition!");

    TriangleMatrix<T> result(this->_rows, this->_type);

    for (int i = 0; i < this->_rows; i++) {
        result[i] = (*this)[i] + other[i];
    }

    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::sub(const TriangleMatrix<T>& other) const {
    if (this->_rows != other._rows || this->_type != other._type) throw std::logic_error("Triangle matrices are not compatible for subtraction!");

    TriangleMatrix<T> result(this->_rows, this->_type);

    for (int i = 0; i < this->_rows; i++) {
        result[i] = (*this)[i] - other[i];
    }

    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::mult(const TriangleMatrix<T>& other) const {
    if (this->_columns != other._rows)
        throw std::logic_error("Triangle matrices dimensions do not match for multiplication!");
    if (this->_type != other._type)
        throw std::logic_error("Triangle matrices must have the same type for multiplication!");

    TriangleMatrix<T> result(this->_rows, this->_type);

    if (_type == TriangleType::Upper) {
        for (int i = 0; i < this->_rows; i++) {
            for (int j = i; j < this->_columns; j++) {
                MathVector<T> row_part(j - i + 1);
                MathVector<T> col_vec(j - i + 1);

                for (int k = 0; k <= j - i; k++)
                    row_part[k] = (*this)[i][k];

                for (int k = i; k <= j; k++)
                    col_vec[k - i] = other[k][j - k];

                result[i][j - i] = row_part * col_vec;
            }
        }
    }

    else {
        for (int i = 0; i < this->_rows; i++) {
            for (int j = 0; j <= i; j++) {
                MathVector<T> row_part(i - j + 1);
                MathVector<T> col_vec(i - j + 1);

                for (int k = 0; k <= i - j; k++)
                    row_part[k] = (*this)[i][k + j];

                for (int k = j; k <= i; k++)
                    col_vec[k - j] = other[k][j];

                result[i][j] = row_part * col_vec;
            }
        }
    }


    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::mult_by_number(const T& number) const {
    TriangleMatrix<T> result(this->_rows, this->_type);

    for (int i = 0; i < this->_rows; i++) {
        result[i] = (*this)[i] * number;
    }

    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::div_by_number(const T& number) const {
    if (number == T()) throw std::logic_error("Division by zero!");

    TriangleMatrix<T> result(this->_rows, this->_type);

    for (int i = 0; i < this->_rows; i++) {
        result[i] = (*this)[i] / number;
    }

    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::transpose() const {
    TriangleMatrix<T> result(this->_rows, this->_type == TriangleType::Upper ? TriangleType::Lower : TriangleType::Upper);

    for (int i = 0; i < this->_rows; ++i) {
        for (int j = 0; j < this->_rows; ++j) {
            if (this->_type == TriangleType::Upper && j >= i) {
                result(j, i) = (*this)(i, j);
            }
            else if (this->_type == TriangleType::Lower && j <= i) {
                result(j, i) = (*this)(i, j);
            }
        }
    }

    return result;
}

// Operators //
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
    return this->add(other);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
    return this->sub(other);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
    return this->mult(other);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const T& other) const {
    return this->mult_by_number(other);
}

template<class T>
TriangleMatrix<T> operator*(const T& other, const TriangleMatrix<T>& matrix) {
    return matrix * other;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator/(const T& other) const {
    return this->div_by_number(other);
}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
    *this = *this + other;
    return *this;
}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
    *this = *this - other;
    return *this;
}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const TriangleMatrix<T>& other) {
    *this = *this * other;
    return *this;
}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const T& other) {
    *this = *this * other;
    return *this;
}

template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator/=(const T& other) {
    *this = *this / other;
    return *this;
}

template<class T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
    if (this->_rows != other._rows || this->_type != other._type) return false;

    for (int i = 0; i < this->_rows; i++) {
        if ((*this)[i] != other[i]) return false;
    }

    return true;
}

template<class T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other) const {
    return !(*this == other);
}

template<class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {
    for (int i = 0; i < matrix._rows; i++) {
        if (matrix._type == TriangleType::Upper) {
            for (int j = 0; j < i; j++) out << T() << " ";
            for (int j = i; j < matrix._columns; j++) out << matrix[i][j - i] << " ";
        }
        else { 
            for (int j = 0; j <= i; j++) out << matrix[i][j] << " ";
            for (int j = i + 1; j < matrix._columns; j++) out << T() << " ";
        }
        out << std::endl;
    }
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matrix) {
    for (int i = 0; i < matrix._rows; i++) {
        if (matrix._type == TriangleType::Upper) {
            for (int j = 0; j < i; j++) {
                T tmp;
                in >> tmp; 
            }
            for (int j = i; j < matrix._columns; j++) {
                in >> matrix[i][j - i];
            }
        }
        else {
            for (int j = 0; j <= i; j++) in >> matrix[i][j];
            for (int j = i + 1; j < matrix._columns; j++) {
                T tmp;
                in >> tmp;
            }
        }
    }
    return in;
}

template<class T>
MathVector<T>& TriangleMatrix<T>::operator[](int index) {
    if (index < 0 || index >= this->_rows) throw std::out_of_range("Index out of range");

    if (this->_type == TriangleType::Upper) {
        return this->data()[index];
    }
    else { 
        return this->data()[index]; 
    }
}

template<class T>
const MathVector<T>& TriangleMatrix<T>::operator[](int index) const {
    if (index < 0 || index >= this->_rows) throw std::out_of_range("Index out of range");

    return this->data()[index];
}

template<class T>
T& TriangleMatrix<T>::operator()(int i, int j) {
    if (i < 0 || i >= this->_rows || j < 0 || j >= this->_rows)
        throw std::out_of_range("Index out of range");

    if (this->_type == TriangleType::Upper) {
        if (j < i)
            throw std::out_of_range("Accessing element below upper triangle");
        return this->data()[i][j - i]; // элементы в строках укорочены
    }
    else { // Lower
        if (j > i)
            throw std::out_of_range("Accessing element above lower triangle");
        return this->data()[i][j]; // нижняя треугольная часть
    }
}

template<class T>
const T& TriangleMatrix<T>::operator()(int i, int j) const {
    if (i < 0 || i >= this->_rows || j < 0 || j >= this->_rows)
        throw std::out_of_range("Index out of range");

    if (this->_type == TriangleType::Upper) {
        if (j < i)
            return T{}; // можно вернуть 0, если хочешь не выбрасывать исключение
        return this->data()[i][j - i];
    }
    else {
        if (j > i)
            return T{};
        return this->data()[i][j];
    }
}