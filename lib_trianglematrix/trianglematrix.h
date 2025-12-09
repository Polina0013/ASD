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
    TriangleMatrix(const Matrix<T>&);
    TriangleMatrix(std::initializer_list<std::initializer_list<T>>, TriangleType);
    TriangleMatrix(const TriangleMatrix<T>&);

    // Destructor //
    ~TriangleMatrix();

    TriangleType get_type() const noexcept;

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

    //friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix);
    //friend std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matrix);

    MathVector<T>& operator[](int index);
    const MathVector<T>& operator[](int index) const;
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
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> other, TriangleType t) : Matrix<T>(), _type(t) {

    this->_rows = static_cast<int>(other.size());
    if (this->_rows == 0) {
        this->_columns = 0;
        return;
    }
    this->_columns = this->_rows;

    this->clear();

    int i = 0;
    for (const auto& row_list : other) {
        int actual_size = static_cast<int>(row_list.size());
        int expected_size;

        if (_type == TriangleType::Upper) {
            expected_size = this->_columns - i;
        }
        else {
            expected_size = i + 1;
        }

        if (actual_size != expected_size) {
            throw std::logic_error("Invalid row length for triangular matrix! Row " +
                std::to_string(i) + " expected size " +
                std::to_string(expected_size) + ", got " +
                std::to_string(actual_size));
        }

        MathVector<T> row(expected_size);

        const T* list_begin = row_list.begin();
        for (int j = 0; j < expected_size; ++j) {
            row[j] = list_begin[j];
        }

        this->push_back(row);
        i++;
    }
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const Matrix<T>& other) {
    if (other.get_rows() == 0) throw std::logic_error("Matrix cannot be empty!");
    if (other.get_rows() != other.get_columns()) throw std::logic_error("Matrix must be square!");

    int size = other.get_rows();

    T tolerance = T(1e-10);
    bool has_upper_non_zero = false;
    bool has_lower_non_zero = false;

    Matrix<T> full_matrix(other);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (std::abs(full_matrix[i][j]) > tolerance) has_upper_non_zero = true;
            if (std::abs(full_matrix[j][i]) > tolerance) has_lower_non_zero = true;
        }
    }

    TriangleType type;
    if (!has_lower_non_zero && has_upper_non_zero) type = TriangleType::Upper;
    else if (has_lower_non_zero && !has_upper_non_zero) type = TriangleType::Lower;
    else if (!has_lower_non_zero && !has_upper_non_zero) type = TriangleType::Upper; // Диагональная
    else throw std::logic_error("Matrix is not triangular! Has non-zero elements both above and below diagonal");

    this->_rows = size;
    this->_columns = size;
    this->_type = type;

    this->clear();

    if (type == TriangleType::Upper) {
        for (int i = 0; i < size; i++) {
            MathVector<T> row(size - i);
            for (int j = i; j < size; j++) {
                row[j - i] = other[i][j];
            }
            this->push_back(row);
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            MathVector<T> row(i + 1);
            for (int j = 0; j <= i; j++) {
                row[j] = other[i][j];
            }
            this->push_back(row);
        }
    }
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other.get_rows(), other.get_columns()), _type(other._type) {
    if (_type == TriangleType::Upper) {
        for (int i = 0; i < this->_rows; ++i) {
            int row_size = this->_columns - i;
            MathVector<T> row(row_size);

            const MathVector<T>& other_row = other[i];
            for (int j = 0; j < row_size; ++j) {
                row[j] = other_row[j];
            }

            (*this)[i] = row;
        }
    }
    else {
        for (int i = 0; i < this->_rows; ++i) {
            int row_size = i + 1;
            MathVector<T> row(row_size);

            const MathVector<T>& other_row = other[i];
            for (int j = 0; j < row_size; ++j) {
                row[j] = other_row[j];
            }

            (*this)[i] = row;
        }
    }
}

// Destructor //
template<class T>
TriangleMatrix<T>::~TriangleMatrix() {}

// Getters //
template<class T>
TriangleType TriangleMatrix<T>::get_type() const noexcept { return _type; }

// Functions //
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::add(const TriangleMatrix<T>& other) const {
    if (this->_rows != other._rows || this->_type != other._type) throw std::logic_error("Triangle matrices are not compatible for addition!");
    
    TriangleMatrix<T> result(*this);

    result.Matrix<T>::operator+=(other);

    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::sub(const TriangleMatrix<T>& other) const {
    if (this->_rows != other._rows || this->_type != other._type) throw std::logic_error("Triangle matrices are not compatible for subtraction!");

    Matrix<T> new_this(*this);
    Matrix<T> new_other(other);

    Matrix<T> result_matrix = new_this.sub(new_other);

    return TriangleMatrix<T>(result_matrix);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::mult(const TriangleMatrix<T>& other) const {
    if (this->_columns != other._rows)
        throw std::logic_error("Triangle matrices dimensions do not match for multiplication!");
    if (this->_type != other._type)
        throw std::logic_error("Triangle matrices must have the same type for multiplication!");

    Matrix<T> new_this(*this);
    Matrix<T> new_other(other);

    Matrix<T> result_matrix = new_this.mult(new_other);

    return TriangleMatrix<T>(result_matrix);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::mult_by_number(const T& number) const {
    Matrix<T> new_this(*this);

    Matrix<T> result_matrix = new_this.mult_by_number(number);

    return TriangleMatrix<T>(result_matrix);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::div_by_number(const T& number) const {
    if (number == T()) throw std::logic_error("Division by zero!");

    Matrix<T> new_this(*this);

    Matrix<T> result_matrix = new_this.div_by_number(number);

    return TriangleMatrix<T>(result_matrix);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::transpose() const {
    if (this->_rows == 0 || this->_columns == 0)  return TriangleMatrix<T>();

    Matrix<T> matrix(*this);
    Matrix<T> transposed_matrix = matrix.Matrix<T>::transpose();

    return TriangleMatrix<T>(transposed_matrix);
}

// Operators //
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
    return this->TriangleMatrix<T>::add(other);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
    return this->TriangleMatrix<T>::sub(other);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
    return this->TriangleMatrix<T>::mult(other);
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const T& other) const {
    return this->TriangleMatrix<T>::mult_by_number(other);
}

template<class T>
TriangleMatrix<T> operator*(const T& other, const TriangleMatrix<T>& matrix) {
    return matrix * other;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator/(const T& other) const {
    return this->TriangleMatrix<T>::div_by_number(other);
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

//template<class T>
//bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
//    if (this->_rows != other._rows || this->_type != other._type) return false;
//
//    for (int i = 0; i < this->_rows; i++) {
//        if ((*this)[i] != other[i]) return false;
//    }
//
//    return true;
//}

// ИЛИ

template<class T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
    if (this->_rows != other._rows || this->_type != other._type) return false;

    Matrix<T> this_matrix(*this);
    Matrix<T> other_matrix(other);

    return this_matrix == other_matrix;
}

template<class T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other) const {
    return !(*this == other);
}

template<class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {
    out << Matrix<T>(matrix);
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matrix) {
    Matrix<T> temp_matrix(matrix.get_rows(), matrix.get_columns());
    in >> temp_matrix;

    matrix = TriangleMatrix<T>(temp_matrix);

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
