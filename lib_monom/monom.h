// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <initializer_list>

#define VARS_COUNTER 3
#define EPSILON 1e-10

class Monom {
    double _coeff;
    int _powers[VARS_COUNTER];
public:
    inline Monom();
    inline Monom(double coeff);
    inline Monom(double coeff, const int powers[VARS_COUNTER]);
    inline Monom(double coeff, std::initializer_list<int> powers);
    inline Monom(const Monom& other);
    ~Monom() = default;

    inline double get_coeff() const;
    inline const int* get_powers() const;
    inline int get_power(int index) const;

    inline bool is_zero() const;

    inline Monom add(const Monom& other) const;
    inline Monom sub(const Monom& other) const;
    inline Monom mult(const Monom& other) const;
    inline Monom div(const Monom& other) const;

    inline Monom mult_by_number(double other) const;
    inline Monom div_by_number(double other) const;

    inline double value_at_the_point(double x, double y, double z) const;

    inline bool operator==(const Monom& other) const;
    inline bool operator!=(const Monom& other) const;

    inline Monom& operator=(const Monom& other);

    inline Monom operator+(const Monom& other) const;
    inline Monom operator-(const Monom& other) const;
    inline Monom operator*(const Monom& other) const;
    inline Monom operator/(const Monom& other) const;

    inline Monom operator*(double other) const;
    inline Monom operator/(double other) const;

    inline Monom& operator+=(const Monom& other);
    inline Monom& operator-=(const Monom& other);
    inline Monom& operator*=(const Monom& other);
    inline Monom& operator/=(const Monom& other);

    inline Monom& operator*=(double other);
    inline Monom& operator/=(double other);

    inline Monom operator-() const;

    inline bool operator<(const Monom& other) const;
    inline bool operator>(const Monom& other) const;
    inline bool operator<=(const Monom& other) const;
    inline bool operator>=(const Monom& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Monom& monom);
    //friend std::istream& operator>>(std::istream& in, Monom& monom);
};

inline Monom::Monom() : _coeff(0.0) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = 0;
    }
}
inline Monom::Monom(double coeff) : _coeff(std::abs(coeff) < EPSILON ? 0.0 : coeff), _powers{ 0, 0, 0 } {}
inline Monom::Monom(double coeff, const int powers[VARS_COUNTER]) : _coeff(coeff) {
    if (powers) {
        for (int i = 0; i < VARS_COUNTER; i++) {
            _powers[i] = powers[i];
        }
    }
    else {
        for (int i = 0; i < VARS_COUNTER; i++) {
            _powers[i] = 0;
        }
    }
}
inline Monom::Monom(double coeff, std::initializer_list<int> powers) : _coeff(coeff) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = 0;
    }

    int i = 0;
    for (int p : powers) {
        if (i < VARS_COUNTER) {
            _powers[i] = p;
            i++;
        }
    }
}
inline Monom::Monom(const Monom& other) : _coeff(other._coeff) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = other._powers[i];
    }
}

inline double Monom::get_coeff() const { return _coeff; }
inline const int* Monom::get_powers() const { return _powers; }
inline int Monom::get_power(int index) const {
    if (index < 0 || index >= VARS_COUNTER) throw std::out_of_range("Index out of range");
    return _powers[index];
}

inline bool Monom::is_zero() const { return std::abs(_coeff) < EPSILON; }

inline Monom Monom::add(const Monom& other) const {
    if (*this != other) throw std::logic_error("Cannot add monomials with different powers!");
    return Monom(_coeff + other._coeff, _powers);
}
inline Monom Monom::sub(const Monom& other) const {
    if (*this != other) throw std::logic_error("Cannot add monomials with different powers!");
    return Monom(_coeff - other._coeff, _powers);
}
inline Monom Monom::mult(const Monom& other) const {
    Monom res;
    res._coeff = _coeff * other._coeff;
    for (int i = 0; i < VARS_COUNTER; i++) {
        res._powers[i] = _powers[i] + other._powers[i];
    }

    return res;
}
inline Monom Monom::div(const Monom& other) const {
    if (std::abs(other._coeff) < EPSILON) throw std::logic_error("Division by zero!");

    for (int i = 0; i < VARS_COUNTER; i++) {
        if (_powers[i] < other._powers[i]) throw std::logic_error("Division would result in negative powers!");
    }

    Monom res;
    res._coeff = _coeff / other._coeff;
    for (int i = 0; i < VARS_COUNTER; i++) {
        res._powers[i] = _powers[i] - other._powers[i];
    }

    return res;
}

inline Monom Monom::mult_by_number(double other) const {
    return Monom(_coeff * other, _powers);
}
inline Monom Monom::div_by_number(double other) const {
    if (std::abs(other) < EPSILON) throw std::logic_error("Division by zero!");
    return Monom(_coeff / other, _powers);
}

inline double Monom::value_at_the_point(double x, double y, double z) const {
    return (_coeff * pow(x, _powers[0]) * pow(y, _powers[1]) * pow(z, _powers[2]));
}

inline bool Monom::operator==(const Monom& other) const {
    for (int i = 0; i < VARS_COUNTER; i++) {
        if (_powers[i] != other._powers[i]) return false;
    }
    return true;
}
inline bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

inline Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coeff = other._coeff;
        for (int i = 0; i < VARS_COUNTER; i++) {
            _powers[i] = other._powers[i];
        }
    }
    return *this;
}

inline Monom Monom::operator+(const Monom& other) const {
    return this->add(other);
}
inline Monom Monom::operator-(const Monom& other) const {
    return this->sub(other);
}
inline Monom Monom::operator*(const Monom& other) const {
    return this->mult(other);
}
inline Monom Monom::operator/(const Monom& other) const {
    return this->div(other);
}

inline Monom Monom::operator*(double other) const {
    return this->mult_by_number(other);
}
inline Monom Monom::operator/(double other) const {
    return this->div_by_number(other);
}

inline Monom& Monom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}
inline Monom& Monom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}
inline Monom& Monom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}
inline Monom& Monom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

inline Monom& Monom::operator*=(double other) {
    *this = *this * other;
    return *this;
}
inline Monom& Monom::operator/=(double other) {
    *this = *this / other;
    return *this;
}

inline Monom Monom::operator-() const {
    return Monom(-_coeff, _powers);
}

inline bool Monom::operator<(const Monom& other) const {
    for (int i = 0; i < VARS_COUNTER; i++) {
        if (_powers[i] != other._powers[i]) return _powers[i] > other._powers[i];
    }
    return false;
}
inline bool Monom::operator>(const Monom& other) const {
    return other < *this;
}
inline bool Monom::operator<=(const Monom& other) const {
    return !(other < *this);
}
inline bool Monom::operator>=(const Monom& other) const {
    return !(other > *this);
}

inline std::ostream& operator<<(std::ostream& out, const Monom& monom) {
    if (monom.is_zero()) {
        out << "0";
        return out;
    }

    if (std::abs(monom._coeff - 1.0) > EPSILON &&
        std::abs(monom._coeff + 1.0) > EPSILON) {
        // коэффициент не +-1
        out << monom._coeff;
    }
    else if (std::abs(monom._coeff + 1.0) < EPSILON) {
        // коэффициент равен -1
        out << "-";
    }

    bool hasVars = false;
    char vars[] = { 'x', 'y', 'z' };

    for (int i = 0; i < VARS_COUNTER; i++) {
        if (monom._powers[i] > 0) {
            hasVars = true;
            out << vars[i];
            if (monom._powers[i] > 1) {
                out << "^" << monom._powers[i];
            }
        }
    }

    // нет переменных, коэффициент равен +-1
    if (!hasVars) {
        if (std::abs(monom._coeff - 1.0) < EPSILON) {
            out << "1";
        }
        else if (std::abs(monom._coeff + 1.0) < EPSILON) {
            out << "-1";
        }
    }

    return out;
}
//inline std::istream& operator>>(std::istream& in, Monom& monom) {}