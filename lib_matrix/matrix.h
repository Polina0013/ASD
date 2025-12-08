// Copyright 2025 Pozdnova Polina
// строки, столбцы
// пустая матрица предусмотрена, так как конструктор по умолчанию наследуется от TVector

#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include "..\lib_mathvector\mathvector.h"

template<class T>
class TriangleMatrix;

template<class T>
class Matrix : public MathVector<MathVector<T>> {
protected:
    int _rows, _columns;
public:
    // Constructors //
    Matrix();
    explicit Matrix(int, int);
    Matrix(const MathVector<MathVector<T>>&);
    Matrix(std::initializer_list<std::initializer_list<T>>);
    Matrix(const TriangleMatrix<T>&);
    Matrix(const Matrix<T>&);

    // Destructor //
    ~Matrix();

    // Getters //
    int get_rows() const noexcept;
    int get_columns() const noexcept;

    // Functions //
    Matrix<T> add(const Matrix<T>&) const;
    Matrix<T> sub(const Matrix<T>&) const;
    Matrix<T> mult(const Matrix<T>&) const;
    Matrix<T> mult_by_number(const T&) const;
    Matrix<T> div_by_number(const T&) const;
    Matrix<T> transpose() const;

    // Operators //
    Matrix<T> operator+(const Matrix<T>&) const;
    Matrix<T> operator-(const Matrix<T>&) const;
    Matrix<T> operator*(const Matrix<T>&) const;
    Matrix<T> operator*(const T&) const;
    Matrix<T> operator/(const T&) const;

    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
    Matrix<T>& operator*=(const Matrix<T>&);
    Matrix<T>& operator/=(const T&);
    Matrix<T>& operator*=(const T&);

    bool operator==(const Matrix<T>&) const;
    bool operator!=(const Matrix<T>&) const;
};

// Constructors //
template<class T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>(), _rows(0), _columns(0) {}

template<class T>
Matrix<T>::Matrix(int rows, int columns) : MathVector<MathVector<T>>(), _rows(rows), _columns(columns) {
    if (rows < 0 || columns < 0)
        throw std::logic_error("Matrix dimensions cannot be negative!");

    for (int i = 0; i < rows; ++i)
        this->push_back(MathVector<T>(columns));
}

template<class T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& other) : MathVector<MathVector<T>>(other),
    _rows(other.size()), _columns(other.size() ? other[0].size() : 0) {}

template<class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) : MathVector<MathVector<T>>(),
    _rows(static_cast<int>(init.size())),
    _columns(0) {

    if (_rows == 0) return;

    _columns = static_cast<int>(init.begin()->size());
    for (auto& row : init) {
        if (static_cast<int>(row.size()) != _columns)
            throw std::logic_error("All rows in initializer list must have the same length!");
        this->push_back(MathVector<T>(row));
    }
}

template<class T>
Matrix<T>::Matrix(const TriangleMatrix<T>& other) {
    _rows = other.get_rows();
    _columns = other.get_columns();

    if (_rows == 0 || _columns == 0) return;

    for (int i = 0; i < _rows; ++i) {
        MathVector<T> row;
        row.resize(_columns, T());
        this->push_back(row);
    }

    TriangleType type = other.get_type();

    if (type == TriangleType::Upper) {
        for (int i = 0; i < _rows; ++i) {
            const MathVector<T>& tri_row = other[i];

            for (int j = 0; j < tri_row.size(); ++j) {
                (*this)[i][i + j] = tri_row[j];
            }
        }
    }
    else {
        for (int i = 0; i < _rows; ++i) {
            const MathVector<T>& tri_row = other[i];

            for (int j = 0; j < tri_row.size(); ++j) {
                (*this)[i][j] = tri_row[j];
            }
        }
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other) : MathVector<MathVector<T>>(other), _rows(other._rows), _columns(other._columns) {}

// Destructor //
template<class T>
Matrix<T>::~Matrix() {}

// Getters //
template<class T>
int Matrix<T>::get_rows() const noexcept { return _rows; }

template<class T>
int Matrix<T>::get_columns() const noexcept { return _columns; }

// Functions //
template<class T>
Matrix<T> Matrix<T>::add(const Matrix<T>& other) const {
    if (_rows != other._rows || _columns != other._columns) throw std::logic_error("Matrix sizes do not match for addition!");

    return this->MathVector<MathVector<T>>::operator+(other);
}

template<class T>
Matrix<T> Matrix<T>::sub(const Matrix<T>& other) const {
    if (_rows != other._rows || _columns != other._columns) throw std::logic_error("Matrix sizes do not match for subtraction!");

    return this->MathVector<MathVector<T>>::operator-(other);
}

template<class T>
Matrix<T> Matrix<T>::mult(const Matrix<T>& other) const {
    if (_columns != other._rows) throw std::logic_error("Matrix dimensions do not match for multiplication!");

    Matrix<T> result(_rows, other._columns);
    Matrix<T> otherT = other.transpose();

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            result[i][j] = (*this)[i] * otherT[j];
        }
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::mult_by_number(const T& other) const {
    Matrix<T> result(_rows, _columns);

    for (int i = 0; i < _rows; i++) {
        result[i] = (*this)[i] * other;
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::div_by_number(const T& other) const {
    if (other == T()) throw std::logic_error("Division by zero!");
    
    Matrix<T> result(_rows, _columns);

    for (int i = 0; i < _rows; i++) {
        result[i] = (*this)[i] / other;
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::transpose() const {
    if (_rows == 0 || _columns == 0) return Matrix<T>();

    Matrix<T> result(_columns, _rows);

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            result[j][i] = (*this)[i][j];
        }
    }

    return result;
}

// Operators //
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    return this->add(other);
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    return this->sub(other);
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    return this->mult(other);
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T& other) const {
    return this->mult_by_number(other);
}

template<class T>
Matrix<T> operator*(const T& number, const Matrix<T>& matrix) {
    return matrix * number;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const T& other) const {
    return this->div_by_number(other);
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    *this = *this + other;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    *this = *this - other;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    *this = *this * other;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const T& other) {
    *this = *this * other;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(const T& other) {
    *this = *this / other;
    return *this;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (_rows != other._rows || _columns != other._columns) return false;

    if (_rows == 0 || _columns == 0) return true;

    return this->MathVector<MathVector<T>>::operator==(other);
}

template<class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
    return !(*this == other);
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    if (matrix.get_rows() == 0 || matrix.get_columns() == 0) {
        return out << "[ Empty Matrix ]\n";
    }
    out << "v" << "\n";
    for (int i = 0; i < matrix.get_rows(); ++i) {
        for (int j = 0; j < matrix.get_columns(); ++j)
            out << matrix[i][j] << ' ';
        out << '\n';
    }
    out << "^" << "\n";
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    int rows = matrix.get_rows();
    int columns = matrix.get_columns();

    if (rows == 0 || columns == 0) throw std::logic_error("Matrix dimensions are zero; cannot input elements.");

    std::cout << "Enter elements (" << rows << "x" << columns << "):\n";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            in >> matrix[i][j];

    return in;
}