#pragma once

#include <iostream>

#include <iostream>
#include <cmath>
#include <string>
#include "..\lib_point\point.h"

template<class T>
class Circle {
    Point<T> _center;
    T _radius;
public:
    Circle();
    Circle(Point<T> center, T radius);
    Circle(T center_x, T center_y, T radius);
    Circle(const Circle<T>& other);

    void set_center(Point<T> center);
    void set_radius(T radius);

    Point<T> get_center() const;
    T get_radius() const;

    template<class U>
    friend std::ostream& operator<<(std::ostream&, const Circle<U>&);

    template<class U>
    friend std::istream& operator>>(std::istream&, Circle<U>&);

    std::string check_relative_location(const Circle<T>& other) const;
};

template<class T>
Circle<T>::Circle() : _center(Point<T>()), _radius(T()) {}

template<class T>
Circle<T>::Circle(Point<T> center, T radius) {
    _center = center;
    set_radius(radius);
}

template<class T>
Circle<T>::Circle(T center_x, T center_y, T radius) {
    Point<T> center(center_x, center_y);
    _center = center;
    set_radius(radius);
    //_radius = radius;
}

template<class T>
Circle<T>::Circle(const Circle<T>& other) : _center(other._center), _radius(other._radius) {}

template<class T>
void Circle<T>::set_center(Point<T> center) { _center = center; }

template<class T>
void Circle<T>::set_radius(T radius) {
    if (radius <= 0) throw std::logic_error("The radius cannot be less than zero!");
    _radius = radius;
}

template<class T>
Point<T> Circle<T>::get_center() const { return _center; }

template<class T>
T Circle<T>::get_radius() const { return _radius; }

template<class T>
std::ostream& operator<<(std::ostream& out, const Circle<T>& circle) {
    out << "[" << circle._center << ", " << circle._radius << "]";
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, Circle<T>& circle) {
    in >> circle._center >> circle._radius;
    return in;
}

template<class T>
std::string Circle<T>::check_relative_location(const Circle<T>& other) const {
    T distance_x = _center.get_x() - other._center.get_x();
    T distance_y = _center.get_y() - other._center.get_y();
    T distance = std::sqrt(distance_x * distance_x + distance_y * distance_y);

    T r1 = _radius;
    T r2 = other._radius;
    T sum_radius = r1 + r2;
    T diff_radii = std::abs(r1 - r2);

    if (distance == 0 && r1 == r2) {
        return "The circles match";
    }
    else if (distance > sum_radius) {
        return "The circles do not intersect or touch";
    }
    else if (distance == sum_radius) {
        return "The circles touch at one point (externally)";
    }
    else if (distance < sum_radius && distance > diff_radii) {
        return "The circles intersect at two points";
    }
    else if (distance <= diff_radii) {
        return "One circle is inside the other";
    };

    return "-1";
}