// Copyright 2026 Pozdnova Polina

#include "..\lib_polynom\polynom.h"

Polynom::Polynom() : _polynom(), _name("") {}
Polynom::Polynom(const Monom& monom) : _polynom(), _name("") {
    if (!monom.is_zero()) _polynom.push_back(monom);
}
Polynom::Polynom(const Monom& monom, const std::string& name)
    : _polynom(), _name(name) {
    if (!monom.is_zero()) _polynom.push_back(monom);
}
Polynom::Polynom(const std::string& str) : _polynom(), _name("") {
    if (str.empty()) return;

    std::string poly_str = str;

    // P = x^2 + y
    size_t eq_pos = poly_str.find('=');
    if (eq_pos != std::string::npos) {
        std::string name_str = poly_str.substr(0, eq_pos);
        name_str.erase(remove(name_str.begin(), name_str.end(), ' '), name_str.end());
        if (!name_str.empty()) {
            _name = name_str;
        }

        poly_str = poly_str.substr(eq_pos + 1);
    }

    poly_str.erase(remove(poly_str.begin(), poly_str.end(), ' '), poly_str.end());

    if (poly_str.empty() || poly_str == "0") return;

    size_t pos = 0;

    while (pos < poly_str.length()) {
        double sign = 1.0;
        if (poly_str[pos] == '+') {
            pos++;
        }
        else if (poly_str[pos] == '-') {
            sign = -1.0;
            pos++;
        }

        if (pos >= poly_str.length()) {
            throw std::logic_error("Unexpected end of string after sign!");
        }

        size_t monom_end = pos;
        while (monom_end < poly_str.length() &&
            poly_str[monom_end] != '+' &&
            poly_str[monom_end] != '-') {
            monom_end++;
        }

        std::string monom_str = poly_str.substr(pos, monom_end - pos);

        Monom monom;
        try {
            monom = Monom(monom_str);
        }
        catch (const std::logic_error& e) {
            throw std::logic_error("Error parsing monomial '" + monom_str + "': " + e.what());
        }

        if (sign < 0) {
            monom = -monom;
        }

        this->insert_sorted(monom);

        pos = monom_end;
    }
}
Polynom::Polynom(const Polynom& other) : _polynom(other._polynom), _name(other._name) {}

void Polynom::set_name(const std::string& name) { _name = name; }
const std::string& Polynom::get_name() const {
    return _name;
}

bool Polynom::is_zero() const {
    if (_polynom.is_empty()) return true;

    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        if (!it->is_zero()) return false;
    }

    return true;
}

Polynom Polynom::add(const Polynom& other) const {
    return merge(*this, other);
}
Polynom Polynom::sub(const Polynom& other) const {
    return merge(*this, -other);
}
Polynom Polynom::mult(const Polynom& other) const {
    Polynom result;

    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2) {
            Monom product = (*it1) * (*it2);
            if (!product.is_zero()) {
                result.insert_sorted(product);
            }
        }
    }

    return result;

}
Polynom Polynom::div(const Polynom& other) const {
    return divmod(other).first;
}
Polynom Polynom::mod(const Polynom& other) const {
    return divmod(other).second;
}
std::pair<Polynom, Polynom> Polynom::divmod(const Polynom& other) const {
    if (other.is_zero()) throw std::logic_error("Division by zero!");

    Polynom quotient;
    Polynom remainder = *this;

    while (!remainder.is_zero()) {
        Monom remainder_leading = *remainder._polynom.begin();
        Monom divisor_leading = *other._polynom.begin();

        if (!can_divide(remainder_leading, divisor_leading)) {
            break;
        }

        try {
            Monom quotient_term = remainder_leading / divisor_leading;

            quotient.insert_sorted(quotient_term);

            Polynom to_sub;
            for (auto it = other._polynom.begin(); it != other._polynom.end(); it++) {
                Monom product = (*it) * quotient_term;
                if (!product.is_zero()) {
                    to_sub.insert_sorted(product);
                }
            }
            remainder = merge(remainder, -to_sub);

        }
        catch (const std::logic_error& e) {
            break;
        }
    }

    return { quotient, remainder };
}

Polynom Polynom::add_a_monom(const Monom& other) const {
    return *this + Polynom(other);
}
Polynom Polynom::sub_a_monom(const Monom& other) const {
    return *this - Polynom(other);
}
Polynom Polynom::mult_by_monom(const Monom& other) const {
    return *this * Polynom(other);
}
Polynom Polynom::div_by_monom(const Monom& other) const {
    return *this / Polynom(other);
}
Polynom Polynom::mod_by_monom(const Monom& other) const {
    return *this % Polynom(other);
}
std::pair<Polynom, Polynom> Polynom::divmod_by_monom(const Monom& other) const {
    return this->divmod(Polynom(other));
}

Polynom Polynom::add_a_number(double other) const {
    return *this + Monom(other);
}
Polynom Polynom::sub_a_number(double other) const {
    return *this - Monom(other);
}
Polynom Polynom::mult_by_number(double other) const {
    return *this * Monom(other);
}
Polynom Polynom::div_by_number(double other) const {
    return *this / Monom(other);
}

double Polynom::value_at_the_point(double x, double y, double z) const {
    if (_polynom.is_empty()) return 0.0;

    double res = 0.0;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        res += it->value_at_the_point(x, y, z);
    }

    return res;
}

std::string Polynom::to_string() const {
    if (is_zero()) {
        return "0";
    }

    std::string result;
    auto it = _polynom.begin();
    result += it->to_string();
    it++;

    for (; it != _polynom.end(); it++) {
        const Monom& monom = *it;

        if (monom.get_coeff() < 0) result += " " + monom.to_string();
        else result += " + " + monom.to_string();
    }

    return result;
}

Polynom Polynom::operator-() const {
    Polynom result;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        result.insert_sorted(-(*it));
    }
    result._name = _name;
    return result;
}
Polynom Polynom::operator+(const Polynom& other) const {
    return this->add(other);
}
Polynom Polynom::operator-(const Polynom& other) const {
    return this->sub(other);
}
Polynom Polynom::operator*(const Polynom& other) const {
    return this->mult(other);
}
Polynom Polynom::operator/(const Polynom& other) const {
    return this->div(other);
}
Polynom Polynom::operator%(const Polynom& other) const {
    return this->mod(other);
}

Polynom Polynom::operator+(const Monom& other) const {
    return this->add_a_monom(other);
}
Polynom Polynom::operator-(const Monom& other) const {
    return this->sub_a_monom(other);
}
Polynom Polynom::operator*(const Monom& other) const {
    return this->mult_by_monom(other);
}
Polynom Polynom::operator/(const Monom& other) const {
    return this->div_by_monom(other);
}
Polynom Polynom::operator%(const Monom& other) const {
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

Polynom Polynom::operator+(double other) const {
    return this->add_a_number(other);
}
Polynom Polynom::operator-(double other) const {
    return this->sub_a_number(other);
}
Polynom Polynom::operator*(double other) const {
    return this->mult_by_number(other);
}
Polynom Polynom::operator/(double other) const {
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

Polynom& Polynom::operator+=(const Polynom& other) {
    *this = merge(*this, other);
    return *this;
}
Polynom& Polynom::operator-=(const Polynom& other) {
    *this = merge(*this, -other);
    return *this;
}
Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}
Polynom& Polynom::operator/=(const Polynom& other) {
    *this = *this / other;
    return *this;
}

Polynom& Polynom::operator+=(const Monom& other) {
    this->insert_sorted(other);
    return *this;
}
Polynom& Polynom::operator-=(const Monom& other) {
    this->insert_sorted(-other);
    return *this;
}
Polynom& Polynom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}
Polynom& Polynom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

Polynom& Polynom::operator+=(double other) {
    *this = *this + other;
    return *this;
}
Polynom& Polynom::operator-=(double other) {
    *this = *this - other;
    return *this;
}
Polynom& Polynom::operator*=(double other) {
    *this = *this * other;
    return *this;
}
Polynom& Polynom::operator/=(double other) {
    *this = *this / other;
    return *this;
}

bool Polynom::operator==(const Polynom& other) const {
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    for (; it1 != _polynom.end() && it2 != other._polynom.end(); it1++, it2++) {
        if (*it1 != *it2) return false;
    }

    return it1 == _polynom.end() && it2 == other._polynom.end();
}
bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _polynom = other._polynom;
        _name = other._name;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Polynom& polynom) {
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
std::istream& operator>>(std::istream& in, Polynom& polynom) {
    std::string poly_str;
    std::getline(in, poly_str);

    try {
        polynom = Polynom(poly_str);
    }
    catch (const std::logic_error& e) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

bool Polynom::check_powers(const Polynom& other) const {
    if (_polynom.is_empty()) return true;
    if (other._polynom.is_empty()) return false;

    int max_dividend[VARS_COUNTER] = { 0 };
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        for (int i = 0; i < VARS_COUNTER; i++) {
            int power = it->get_power(i);
            if (power > max_dividend[i]) max_dividend[i] = power;
        }
    }

    int max_divisor[VARS_COUNTER] = { 0 };
    for (auto it = other._polynom.begin(); it != other._polynom.end(); it++) {
        for (int i = 0; i < VARS_COUNTER; i++) {
            int power = it->get_power(i);
            if (power > max_divisor[i]) max_divisor[i] = power;
        }
    }

    for (int i = 0; i < VARS_COUNTER; i++) {
        if (max_divisor[i] > max_dividend[i]) return false;
    }

    return true;
}
bool Polynom::can_divide(const Monom& dividend, const Monom& divisor) const {
    for (int i = 0; i < VARS_COUNTER; i++) {
        if (dividend.get_power(i) < divisor.get_power(i)) {
            return false;
        }
    }
    return true;
}
void Polynom::insert_sorted(const Monom& monom) {
    if (monom.is_zero()) return;

    if (_polynom.is_empty()) {
        _polynom.push_back(monom);
        return;
    }

    auto it = _polynom.begin();
    auto prev_it = _polynom.end();

    while (it != _polynom.end()) {
        if (*it == monom) {
            Monom sum = *it + monom;
            if (sum.is_zero()) {
                auto node_to_delete = it.get_node();
                it++;
                _polynom.erase(node_to_delete);
            }
            else {
                *it = sum;
            }
            return;
        }
        else if (monom > *it) {
            if (prev_it == _polynom.end()) {
                _polynom.push_front(monom);
            }
            else {
                _polynom.insert(prev_it.get_node(), monom);
            }
            return;
        }
        prev_it = it;
        it++;
    }

    _polynom.push_back(monom);
}
Polynom Polynom::merge(const Polynom& a, const Polynom& b) const {
    Polynom result;

    auto it1 = a._polynom.begin();
    auto it2 = b._polynom.begin();

    while (it1 != a._polynom.end() && it2 != b._polynom.end()) {
        if (*it1 == *it2) {
            Monom sum = *it1 + *it2;
            if (!sum.is_zero()) {
                result._polynom.push_back(sum);
            }
            it1++;
            it2++;
        }
        else if (*it1 > *it2) {
            result._polynom.push_back(*it1);
            it1++;
        }
        else {
            result._polynom.push_back(*it2);
            it2++;
        }
    }

    while (it1 != a._polynom.end()) {
        result._polynom.push_back(*it1);
        ++it1;
    }

    while (it2 != b._polynom.end()) {
        result._polynom.push_back(*it2);
        ++it2;
    }

    return result;
}