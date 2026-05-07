// Copyright 2026 Pozdnova Polina

#pragma once

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <initializer_list>
#include <string>

#define VARS_COUNTER 3
#define EPSILON 1e-10

class Monom {
    double _coeff;
    int _powers[VARS_COUNTER];
public:
    Monom();
    Monom(double coeff);
    Monom(double coeff, const int powers[VARS_COUNTER]);
    Monom(double coeff, std::initializer_list<int> powers);
    Monom(std::string monom_str);
    Monom(const Monom& other);
    ~Monom() = default;

    double get_coeff() const;
    const int* get_powers() const;
    int get_power(int index) const;

    bool is_zero() const;

    Monom add(const Monom& other) const;
    Monom sub(const Monom& other) const;
    Monom mult(const Monom& other) const;
    Monom div(const Monom& other) const;

    Monom mult_by_number(double other) const;
    Monom div_by_number(double other) const;

    double value_at_the_point(double x, double y, double z) const;

    std::string to_string() const;

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    Monom& operator=(const Monom& other);

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double other) const;
    Monom operator/(double other) const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);

    Monom& operator*=(double other);
    Monom& operator/=(double other);

    Monom operator-() const;

    bool operator<(const Monom& other) const;
    bool operator>(const Monom& other) const;
    bool operator<=(const Monom& other) const;
    bool operator>=(const Monom& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Monom& monom);
    friend std::istream& operator>>(std::istream& in, Monom& monom);
};