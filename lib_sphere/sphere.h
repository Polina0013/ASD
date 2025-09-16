#pragma once

#include <iostream>
#include <cctype>
#include <string>

#include "..\lib_point3D\point3D.h"

template<class T>
class Sphere {
    Point3D<T> _center;
    T _radius;
public:
    Sphere();
    Sphere(Point3D<T> center, T radius);
    Sphere(T center_x, T center_y, T center_z, T radius);
    Sphere(const Sphere<T>& other);

    void set_center(Point3D<T> center);
    void set_radius(T radius);

    Point3D<T> get_center() const;
    T get_radius() const;

    template<class U>
    friend std::ostream& operator<<(std::ostream&, const Sphere<U>&);

    template<class U>
    friend std::istream& operator>>(std::istream&, const Sphere<U>&);

    std::string check_relative_location(const Sphere<T>& other) const;
};

template<class T>
Sphere<T>::Sphere() : _center(Point3D<T>()), _radius(T()) {}

template<class T>
Sphere<T>::Sphere(Point3D<T> center, T radius) {
    set_center(center);
    set_radius(radius);
}

template<class T>
Sphere<T>::Sphere(T center_x, T center_y, T center_z, T radius) {
    Point3D<T> center(center_x, center_y, center_z);
    set_center(center);
    set_radius(radius);
}

template<class T>
Sphere<T>::Sphere(const Sphere<T>& other) : _center(other._center), _radius(other._radius) {}

template<class T>
void Sphere<T>::set_center(Point3D<T> center) { _center = center; }

template<class T>
void Sphere<T>::set_radius(T radius) {
    if (radius <= 0) throw std::logic_error("The radius cannot be less than zero!");
    _radius = radius;
}

template<class T>
Point3D<T> Sphere<T>::get_center() const { return _center; }

template<class T>
T Sphere<T>::get_radius() const { return _radius; }

template<class T>
std::ostream& operator<<(std::ostream& out, const Sphere<T>& sphere) {
    out << "[" << sphere._center << ", " << sphere._radius << "]";
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, Sphere<T>& sphere) {
    in >> sphere._center >> sphere._radius;
    return in;
}

template<class T>
std::string Sphere<T>::check_relative_location(const Sphere<T>& other) const {
    T distance_x = _center.get_x() - other._center.get_x();
    T distance_y = _center.get_y() - other._center.get_y();
    T distance_z = _center.get_z() - other._center.get_z();
    T distance = std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);

    T r1 = _radius;
    T r2 = other._radius;
    T sum_radius = r1 + r2;
    T diff_radii = std::abs(r1 - r2);

    if (distance == 0 && r1 == r2) {
        return "The spheres match";
    }
    else if (distance > sum_radius) {
        return "The spheres do not intersect or touch";
    }
    else if (distance == sum_radius) {
        return "The spheres touch at one point (externally)";
    }
    else if (distance < sum_radius && distance > diff_radii) {
        return "The spheres intersect in a circle";
    }
    else if (distance == diff_radii && distance != 0) {
        return "The spheres touch at one point (internally)";
    }
    else if (distance < diff_radii) {
        if (r1 > r2) {
            return "One sphere is completely inside the other (smaller inside larger)";
        }
        else {
            return "One sphere is completely inside the other (larger contains smaller)";
        }
    }
    else if (distance == 0 && r1 != r2) {
        return "Concentric spheres (one inside the other)";
    }

    return "Unknown relationship";
}
