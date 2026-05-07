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
    Polynom();
    Polynom(const Monom& monom);
    Polynom(const Monom& monom, const std::string& name);
    Polynom(const std::string& polynom_str);
    Polynom(const Polynom& other);
    ~Polynom() = default;

    void set_name(const std::string& name);
    const std::string& get_name() const;

    bool is_zero() const;

    Polynom add(const Polynom& other) const;
    Polynom sub(const Polynom& other) const;
    Polynom mult(const Polynom& other) const;
    Polynom div(const Polynom& other) const;
    Polynom mod(const Polynom& other) const;
    std::pair<Polynom, Polynom> divmod(const Polynom& other) const;

    Polynom add_a_monom(const Monom& other) const;
    Polynom sub_a_monom(const Monom& other) const;
    Polynom mult_by_monom(const Monom& other) const;
    Polynom div_by_monom(const Monom& other) const;
    Polynom mod_by_monom(const Monom& other) const;
    std::pair<Polynom, Polynom> divmod_by_monom(const Monom& other) const;

    Polynom add_a_number(double other) const;
    Polynom sub_a_number(double other) const;
    Polynom mult_by_number(double other) const;
    Polynom div_by_number(double other) const;

    double value_at_the_point(double x, double y, double z) const;

    Polynom operator-() const;

    std::string to_string() const;

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator/(const Polynom& other) const;
    Polynom operator%(const Polynom& other) const;

    Polynom operator+(const Monom& other) const;
    Polynom operator-(const Monom& other) const;
    Polynom operator*(const Monom& other) const;
    Polynom operator/(const Monom& other) const;
    Polynom operator%(const Monom& other) const;

    friend Polynom operator+(const Monom& monom, const Polynom& polynom);
    friend Polynom operator-(const Monom& monom, const Polynom& polynom);
    friend Polynom operator*(const Monom& monom, const Polynom& polynom);
    friend Polynom operator/(const Monom& monom, const Polynom& polynom);
    friend Polynom operator%(const Monom& monom, const Polynom& polynom);

    Polynom operator+(double other) const;
    Polynom operator-(double other) const;
    Polynom operator*(double other) const;
    Polynom operator/(double other) const;

    friend Polynom operator+(double number, const Polynom& polynom);
    friend Polynom operator-(double number, const Polynom& polynom);
    friend Polynom operator*(double number, const Polynom& polynom);
    friend Polynom operator/(double number, const Polynom& polynom);

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator/=(const Polynom& other);

    Polynom& operator+=(const Monom& other);
    Polynom& operator-=(const Monom& other);
    Polynom& operator*=(const Monom& other);
    Polynom& operator/=(const Monom& other);

    Polynom& operator+=(double other);
    Polynom& operator-=(double other);
    Polynom& operator*=(double other);
    Polynom& operator/=(double other);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    Polynom& operator=(const Polynom& other);

    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);
    friend std::istream& operator>>(std::istream& in, Polynom& monom);
private:
    bool check_powers(const Polynom& other) const;
    bool can_divide(const Monom& dividend, const Monom& divisor) const;
    void insert_sorted(const Monom& monom);
    Polynom merge(const Polynom& a, const Polynom& b) const;
};