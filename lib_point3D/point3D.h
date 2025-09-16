#pragma once

#include <iostream>
#include <cctype>

#include "..\lib_point\point.h"

template<class T>
class Point3D : public Point<T> {
protected:
    T _z;
public:
    Point3D();
    Point3D(T x, T y, T z);
    Point3D(const Point3D<T>& other);
    Point3D(const Point<T>& other);

    void set_z(T z);

    T get_z() const;

    //template<class U>
    //friend std::ostream& operator<<(std::ostream& out, const Point3D<U>& point) {
    //    out << "(" << point.Point<U>::_x << ", " << point.Point<U>::_y << ", " << point._z << ")";
    //    return out;
    //}

    //template<class U>
    //friend std::istream& operator>>(std::istream& in, const Point3D<U>& point) {
    //    in >> point.Point<U>::_x >> point.Point<U>::_y >> point._z;
    //    return in;
    //}
};

template<class T>
Point3D<T>::Point3D() : Point<T>(), _z(0) {}

template<class T>
Point3D<T>::Point3D(T x, T y, T z) : Point<T>(x, y), _z(z) {}

template<class T>
Point3D<T>::Point3D(const Point3D<T>& other) : Point<T>(other), _z(other._z) {}

template<class T>
Point3D<T>::Point3D(const Point<T>& other) : Point<T>(other), _z(T()) {}

template<class T>
void Point3D<T>::set_z(T z) {
    //if (!isdigit(x)) throw std::logic_error("Not a number entered!");
    _z = z;
}

template<class T>
T Point3D<T>::get_z() const { return _z; }
