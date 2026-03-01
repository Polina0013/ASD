// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>

#include "..\lib_monom\monom.h"
#include "..\lib_list\list.h"

#define VARS_COUNTER 3

class Polynom {
    List<Monom> _polynom;
    std::string _name;
public:
    inline Polynom();
    inline Polynom(const Monom& monom);
    inline Polynom(const std::string& str);    // не готово
    inline Polynom(const Polynom& other);
    ~Polynom() = default;

    inline void set_name(const std::string& name);

    inline bool is_zero() const;

    inline Polynom add(const Polynom& other) const;
    inline Polynom sub(const Polynom& other) const;
    inline Polynom mult(const Polynom& other) const;
    inline Polynom div(const Polynom& other) const;
    inline Polynom mod(const Polynom& other) const;
    inline std::pair<Polynom, Polynom> divmod(const Polynom& other) const;

    inline Polynom add_a_monom(const Monom& other) const;
    inline Polynom sub_a_monom(const Monom& other) const;
    inline Polynom mult_by_monom(const Monom& other) const;
    inline Polynom div_by_monom(const Monom& other) const;
    inline Polynom mod_by_monom(const Monom& other) const;
    inline std::pair<Polynom, Polynom> divmod_by_monom(const Monom& other) const;

    inline Polynom add_a_number(double other) const;
    inline Polynom sub_a_number(double other) const;
    inline Polynom mult_by_number(double other) const;
    inline Polynom div_by_number(double other) const;

    inline double value_at_the_point(double x, double y, double z) const;

    inline Polynom operator+(const Polynom& other) const;
    inline Polynom operator-(const Polynom& other) const;
    inline Polynom operator*(const Polynom& other) const;
    inline Polynom operator/(const Polynom& other) const;
    inline Polynom operator%(const Polynom& other) const;

    inline Polynom operator+(const Monom& other) const;
    inline Polynom operator-(const Monom& other) const;
    inline Polynom operator*(const Monom& other) const;
    inline Polynom operator/(const Monom& other) const;
    inline Polynom operator%(const Monom& other) const;

    friend Polynom operator+(const Monom& monom, const Polynom& polynom);
    friend Polynom operator-(const Monom& monom, const Polynom& polynom);
    friend Polynom operator*(const Monom& monom, const Polynom& polynom);
    friend Polynom operator/(const Monom& monom, const Polynom& polynom);
    friend Polynom operator%(const Monom& monom, const Polynom& polynom);

    inline Polynom operator+(double other) const;
    inline Polynom operator-(double other) const;
    inline Polynom operator*(double other) const;
    inline Polynom operator/(double other) const;

    friend Polynom operator+(double number, const Polynom& polynom);
    friend Polynom operator-(double number, const Polynom& polynom);
    friend Polynom operator*(double number, const Polynom& polynom);
    friend Polynom operator/(double number, const Polynom& polynom);

    inline Polynom& operator+=(const Polynom& other);
    inline Polynom& operator-=(const Polynom& other);
    inline Polynom& operator*=(const Polynom& other);
    inline Polynom& operator/=(const Polynom& other);

    inline Polynom& operator+=(const Monom& other);
    inline Polynom& operator-=(const Monom& other);
    inline Polynom& operator*=(const Monom& other);
    inline Polynom& operator/=(const Monom& other);

    inline Polynom& operator+=(double other);
    inline Polynom& operator-=(double other);
    inline Polynom& operator*=(double other);
    inline Polynom& operator/=(double other);

    inline bool operator==(const Polynom& other) const;
    inline bool operator!=(const Polynom& other) const;

    inline Polynom& operator=(const Polynom& other);

    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);

private:
    inline bool check_powers(const Polynom& other) const;
    inline bool can_divide(const Monom& dividend, const Monom& divisor) const;
};

inline Polynom::Polynom() : _polynom(), _name("") {}
inline Polynom::Polynom(const Monom& monom) : _polynom(), _name("") {
    if (!monom.is_zero()) _polynom.push_back(monom);
}
inline Polynom::Polynom(const std::string& str) : _polynom(), _name("") {
    // реализовать парсинг строки
}
inline Polynom::Polynom(const Polynom& other) : _polynom(other._polynom), _name(other._name) {}

inline void Polynom::set_name(const std::string& name) { _name = name; }

inline bool Polynom::is_zero() const {
    if (_polynom.is_empty()) return true;

    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        if (!it->is_zero()) return false;
    }

    return true;
}

inline Polynom Polynom::add(const Polynom& other) const {
    Polynom result;
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 == *it2) {
            Monom sum = *it1 + *it2;
            if (!sum.is_zero()) result._polynom.push_back(sum);
            it1++;
            it2++;
        }
        else if (*it1 < *it2) {
            result._polynom.push_back(*it1);
            it1++;
        }
        else {
            result._polynom.push_back(*it2);
            it2++;
        }
    }

    while (it1 != _polynom.end()) {
        result._polynom.push_back(*it1);
        it1++;
    }
    while (it2 != _polynom.end()) {
        result._polynom.push_back(*it2);
        it2++;
    }

    return result;
}
inline Polynom Polynom::sub(const Polynom& other) const {
    Polynom result;
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 == *it2) {
            Monom diff = *it1 - *it2;
            if (!diff.is_zero()) result._polynom.push_back(diff);
            it1++;
            it2++;
        }
        else if (*it1 < *it2) {
            result._polynom.push_back(*it1);
            it1++;
        }
        else {
            result._polynom.push_back(-(*it2));
            it2++;
        }
    }

    while (it1 != _polynom.end()) {
        result._polynom.push_back(*it1);
        it1++;
    }
    while (it2 != _polynom.end()) {
        result._polynom.push_back(-(*it2));
        it2++;
    }

    return result;
}
inline Polynom Polynom::mult(const Polynom& other) const {
    Polynom result;

    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); it2++) {
            Monom mult = (*it1) * (*it2);
            if (!mult.is_zero()) { result += mult; }
        }
    }

    return result;
}
inline Polynom Polynom::div(const Polynom& other) const {
    return divmod(other).first;
}
inline Polynom Polynom::mod(const Polynom& other) const {
    return divmod(other).second;
}
inline std::pair<Polynom, Polynom> Polynom::divmod(const Polynom& other) const {
    if (other.is_zero()) throw std::logic_error("Division by zero!");

    if (!check_powers(other)) return { Polynom(), *this };

    Polynom quotient;
    Polynom remainder = *this;

    while (!remainder.is_zero()) {
        Monom remainder_leading = *remainder._polynom.begin();
        Monom divisor_leading = *other._polynom.begin();

        if (!can_divide(remainder_leading, divisor_leading)) break;

        Monom quotient_term = remainder_leading / divisor_leading;
        quotient._polynom.push_back(quotient_term);

        Polynom sub_polynom = other * quotient_term;
        remainder = remainder - sub_polynom;
    }

    return { quotient, remainder };
}

inline Polynom Polynom::add_a_monom(const Monom& other) const {
    return *this + Polynom(other);
}
inline Polynom Polynom::sub_a_monom(const Monom& other) const {
    return *this - Polynom(other);
}
inline Polynom Polynom::mult_by_monom(const Monom& other) const {
    return *this * Polynom(other);
}
inline Polynom Polynom::div_by_monom(const Monom& other) const {
    return *this / Polynom(other);
}
inline Polynom Polynom::mod_by_monom(const Monom& other) const {
    return *this % Polynom(other);
}
inline std::pair<Polynom, Polynom> Polynom::divmod_by_monom(const Monom& other) const {
    return this->divmod(Polynom(other));
}

inline Polynom Polynom::add_a_number(double other) const {
    return *this + Monom(other);
}
inline Polynom Polynom::sub_a_number(double other) const {
    return *this - Monom(other);
}
inline Polynom Polynom::mult_by_number(double other) const {
    return *this * Monom(other);
}
inline Polynom Polynom::div_by_number(double other) const {
    return *this / Monom(other);
}

inline double Polynom::value_at_the_point(double x, double y, double z) const {
    if (_polynom.is_empty()) return 0.0;
    
    double res = 0.0;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        res += it->value_at_the_point(x, y, z);
    }

    return res;
}

inline Polynom Polynom::operator+(const Polynom& other) const {
    return this->add(other);
}
inline Polynom Polynom::operator-(const Polynom& other) const {
    return this->sub(other);
}
inline Polynom Polynom::operator*(const Polynom& other) const {
    return this->mult(other);
}
inline Polynom Polynom::operator/(const Polynom& other) const {
    return this->div(other);
}
inline Polynom Polynom::operator%(const Polynom& other) const {
    return this->mod(other);
}

inline Polynom Polynom::operator+(const Monom& other) const {
    return this->add_a_monom(other);
}
inline Polynom Polynom::operator-(const Monom& other) const {
    return this->sub_a_monom(other);
}
inline Polynom Polynom::operator*(const Monom& other) const {
    return this->mult_by_monom(other);
}
inline Polynom Polynom::operator/(const Monom& other) const {
    return this->div_by_monom(other);
}
inline Polynom Polynom::operator%(const Monom& other) const {
    return this->mod_by_monom(other);
}

Polynom operator+(const Monom& monom, const Polynom& polynom) {
    return Polynom(monom) + polynom;
}
Polynom operator-(const Monom& monom, const Polynom& polynom) {
    return Polynom(monom) - polynom;
}
Polynom operator*(const Monom& monom, const Polynom& polynom) {
    return Polynom(monom) * polynom;
}
Polynom operator/(const Monom& monom, const Polynom& polynom) {
    return Polynom(monom) / polynom;
}
Polynom operator%(const Monom& monom, const Polynom& polynom) {
    return Polynom(monom) % polynom;
}

inline Polynom Polynom::operator+(double other) const {
    return this->add_a_number(other);
}
inline Polynom Polynom::operator-(double other) const {
    return this->sub_a_number(other);
}
inline Polynom Polynom::operator*(double other) const {
    return this->mult_by_number(other);
}
inline Polynom Polynom::operator/(double other) const {
    return this->div_by_number(other);
}

Polynom operator+(double number, const Polynom& polynom) {
    return Polynom(number) + polynom;
}
Polynom operator-(double number, const Polynom& polynom) {
    return Polynom(number) - polynom;
}
Polynom operator*(double number, const Polynom& polynom) {
    return Polynom(number) * polynom;
}
Polynom operator/(double number, const Polynom& polynom) {
    return Polynom(number) / polynom;
}

inline Polynom& Polynom::operator+=(const Polynom& other) {
    *this = *this + other;
    return *this;
}
inline Polynom& Polynom::operator-=(const Polynom& other) {
    *this = *this - other;
    return *this;
}
inline Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}
inline Polynom& Polynom::operator/=(const Polynom& other) {
    *this = *this / other;
    return *this;
}

inline Polynom& Polynom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}
inline Polynom& Polynom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}
inline Polynom& Polynom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}
inline Polynom& Polynom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

inline Polynom& Polynom::operator+=(double other) {
    *this = *this + other;
    return *this;
}
inline Polynom& Polynom::operator-=(double other) {
    *this = *this - other;
    return *this;
}
inline Polynom& Polynom::operator*=(double other) {
    *this = *this * other;
    return *this;
}
inline Polynom& Polynom::operator/=(double other) {
    *this = *this / other;
    return *this;
}

inline bool Polynom::operator==(const Polynom& other) const {
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); it2++) {
            if ((*it1) != (*it2)) return false;
        }
    }

    return true;
}
inline bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

inline Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _polynom = other._polynom;
        _name = other._name;
    }
    return *this;
}

inline std::ostream& operator<<(std::ostream& out, const Polynom& polynom) {
    if (polynom.is_zero()) {
        out << "0";
        return out;
    }

    auto it = polynom._polynom.begin();
    out << *it;
    it++;

    for (; it != polynom._polynom.end(); it++) {
        const Monom& monom = *it;

        if (monom.get_coeff() < 0) out << " " << monom;
        else out << " + " << monom;
    }

    return out;
}

inline bool Polynom::check_powers(const Polynom& other) const {
    if (_polynom.is_empty()) return true;
    if (other._polynom.is_empty()) return false;

    int min_num[VARS_COUNTER];
    for (int i = 0; i < VARS_COUNTER; i++) min_num[i] = INT_MAX;

    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        for (int i = 0; i < VARS_COUNTER; i++) {
            int power = it->get_power(i);
            if (power < min_num[i]) min_num[i] = power;
        }
    }

    int max_den[VARS_COUNTER] = { 0 };
    for (auto it = other._polynom.begin(); it != other._polynom.end(); it++) {
        for (int i = 0; i < VARS_COUNTER; i++) {
            int power = it->get_power(i);
            if (power > max_den[i]) max_den[i] = power;
        }
    }

    for (int i = 0; i < VARS_COUNTER; i++) {
        if (max_den[i] > min_num[i]) return false;
    }

    return true;
}
inline bool Polynom::can_divide(const Monom& dividend, const Monom& divisor) const {
    for (int i = 0; i < VARS_COUNTER; i++) {
        if (dividend.get_power(i) < divisor.get_power(i)) {
            return false;
        }
    }
    return true;
}

// ќценить сложности всех алгоритмов O(?)