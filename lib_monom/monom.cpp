// Copyright 2026 Pozdnova Polina

#include "..\lib_monom\monom.h"

Monom::Monom() : _coeff(0.0) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = 0;
    }
}
Monom::Monom(double coeff) : _coeff(std::abs(coeff) < EPSILON ? 0.0 : coeff), _powers{ 0, 0, 0 } {}
Monom::Monom(double coeff, const int powers[VARS_COUNTER]) : _coeff(coeff) {
    if (powers) {
        for (int i = 0; i < VARS_COUNTER; i++) {
            if (powers[i] < 0) throw std::logic_error("Monom degree cannot be negative!");
            _powers[i] = powers[i];
        }
    }
    else {
        for (int i = 0; i < VARS_COUNTER; i++) {
            _powers[i] = 0;
        }
    }
}
Monom::Monom(double coeff, std::initializer_list<int> powers) : _coeff(coeff) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = 0;
    }

    int i = 0;
    for (int p : powers) {
        if (i < VARS_COUNTER) {
            if (p < 0) throw std::logic_error("Monom degree cannot be negative!");
            _powers[i] = p;
            i++;
        }
    }
}
Monom::Monom(std::string monom_str) : _coeff(1.0) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = 0;
    }

    monom_str.erase(remove(monom_str.begin(), monom_str.end(), ' '), monom_str.end());

    if (monom_str.empty() || monom_str == "0") {
        _coeff = 0.0;
        return;
    }

    size_t pos = 0;

    if (monom_str[0] == '+' || monom_str[0] == '-') {
        if (monom_str[0] == '-') _coeff = -1.0;
        pos = 1;
    }

    size_t num_end = pos;
    while (num_end < monom_str.length() &&
        (isdigit(monom_str[num_end]) || monom_str[num_end] == '.')) {
        num_end++;
    }

    if (num_end > pos) {
        std::string num_str = monom_str.substr(pos, num_end - pos);
        double abs_coeff = std::stod(num_str);
        _coeff = (_coeff < 0) ? -abs_coeff : abs_coeff;
        pos = num_end;
    }

    char vars[] = { 'x', 'y', 'z' };

    for (int var_index = 0; var_index < VARS_COUNTER; var_index++) {
        if (pos < monom_str.length() && monom_str[pos] == vars[var_index]) {
            pos++;

            int power = 1;

            if (pos < monom_str.length() && monom_str[pos] == '^') {
                pos++;

                size_t power_start = pos;
                while (pos < monom_str.length() && isdigit(monom_str[pos])) {
                    pos++;
                }

                if (power_start == pos) throw std::logic_error("Expected number after ^ !");

                std::string power_str = monom_str.substr(power_start, pos - power_start);
                power = std::stoi(power_str);

                if (power < 0) throw std::logic_error("Power cannot be negative!");
            }

            _powers[var_index] = power;
        }
    }

    if (pos < monom_str.length()) throw std::logic_error("Unexpected characters after parsing: " + monom_str.substr(pos));

    if (std::abs(_coeff) < EPSILON) {
        _coeff = 0.0;
    }
}
Monom::Monom(const Monom& other) : _coeff(other._coeff) {
    for (int i = 0; i < VARS_COUNTER; i++) {
        _powers[i] = other._powers[i];
    }
}

double Monom::get_coeff() const { return _coeff; }
const int* Monom::get_powers() const { return _powers; }
int Monom::get_power(int index) const {
    if (index < 0 || index >= VARS_COUNTER) throw std::out_of_range("Index out of range");
    return _powers[index];
}

bool Monom::is_zero() const { return std::abs(_coeff) < EPSILON; }

Monom Monom::add(const Monom& other) const {
    if (*this != other) throw std::logic_error("Cannot add monomials with different powers!");
    return Monom(_coeff + other._coeff, _powers);
}
Monom Monom::sub(const Monom& other) const {
    if (*this != other) throw std::logic_error("Cannot add monomials with different powers!");
    return Monom(_coeff - other._coeff, _powers);
}
Monom Monom::mult(const Monom& other) const {
    Monom res;
    res._coeff = _coeff * other._coeff;
    for (int i = 0; i < VARS_COUNTER; i++) {
        res._powers[i] = _powers[i] + other._powers[i];
    }

    return res;
}
Monom Monom::div(const Monom& other) const {
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

Monom Monom::mult_by_number(double other) const {
    return Monom(_coeff * other, _powers);
}
Monom Monom::div_by_number(double other) const {
    if (std::abs(other) < EPSILON) throw std::logic_error("Division by zero!");
    return Monom(_coeff / other, _powers);
}

double Monom::value_at_the_point(double x, double y, double z) const {
    return (_coeff * pow(x, _powers[0]) * pow(y, _powers[1]) * pow(z, _powers[2]));
}

std::string Monom::to_string() const {
    if (is_zero()) {
        return "0";
    }

    std::string result;

    if (std::abs(_coeff - 1.0) > EPSILON &&
        std::abs(_coeff + 1.0) > EPSILON) {
        // коэффициент не +-1
        result += std::to_string(_coeff);
        // убираем нули
        if (result.find('.') != std::string::npos) {
            result.erase(result.find_last_not_of('0') + 1, std::string::npos);
            result.erase(result.find_last_not_of('.') + 1, std::string::npos);
        }
    }
    else if (std::abs(_coeff + 1.0) < EPSILON) {
        // коэффициент равен -1
        result += "-";
    }

    bool hasVars = false;
    char vars[] = { 'x', 'y', 'z' };

    for (int i = 0; i < VARS_COUNTER; i++) {
        if (_powers[i] > 0) {
            hasVars = true;
            result += vars[i];
            if (_powers[i] > 1) {
                result += "^" + std::to_string(_powers[i]);
            }
        }
    }

    // нет переменных, коэффициент равен +-1
    if (!hasVars) {
        if (std::abs(_coeff - 1.0) < EPSILON) {
            result += "1";
        }
        else if (std::abs(_coeff + 1.0) < EPSILON) {
            result += "-1";
        }
    }

    return result;
}

bool Monom::operator==(const Monom& other) const {
    for (int i = 0; i < VARS_COUNTER; i++) {
        if (_powers[i] != other._powers[i]) return false;
    }
    return true;
}
bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coeff = other._coeff;
        for (int i = 0; i < VARS_COUNTER; i++) {
            _powers[i] = other._powers[i];
        }
    }
    return *this;
}

Monom Monom::operator+(const Monom& other) const {
    return this->add(other);
}
Monom Monom::operator-(const Monom& other) const {
    return this->sub(other);
}
Monom Monom::operator*(const Monom& other) const {
    return this->mult(other);
}
Monom Monom::operator/(const Monom& other) const {
    return this->div(other);
}

Monom Monom::operator*(double other) const {
    return this->mult_by_number(other);
}
Monom Monom::operator/(double other) const {
    return this->div_by_number(other);
}

Monom& Monom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}
Monom& Monom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}
Monom& Monom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}
Monom& Monom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

Monom& Monom::operator*=(double other) {
    *this = *this * other;
    return *this;
}
Monom& Monom::operator/=(double other) {
    *this = *this / other;
    return *this;
}

Monom Monom::operator-() const {
    return Monom(-_coeff, _powers);
}

bool Monom::operator>(const Monom& other) const {
    for (int i = 0; i < VARS_COUNTER; i++) {
        if (_powers[i] != other._powers[i]) return _powers[i] > other._powers[i];
    }
    return false;
}
bool Monom::operator<(const Monom& other) const {
    return other > *this;
}

bool Monom::operator<=(const Monom& other) const {
    return !(other < *this);
}
bool Monom::operator>=(const Monom& other) const {
    return !(other > *this);
}

std::ostream& operator<<(std::ostream& out, const Monom& monom) {
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
std::istream& operator>>(std::istream& in, Monom& monom) {
    std::string monom_str;
    in >> monom_str;

    try {
        monom = Monom(monom_str);
    }
    catch (const std::logic_error& e) {
        in.setstate(std::ios::failbit);
    }

    return in;
}