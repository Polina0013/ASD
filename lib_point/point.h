#pragma once

#include <iostream>
#include <cctype>

template<class T>
class Point {
    T _x;
    T _y;
public:
    Point();
    Point(T x, T y);
    Point(const Point<T>& other);

    void set_x(T x);
    void set_y(T y);

    T get_x() const;
    T get_y() const;

    template<class U>
    friend std::ostream& operator<<(std::ostream&, const Point<U>&);

    template<class U>
    friend std::istream& operator>>(std::istream&, Point<U>&);
};

template<class T>
Point<T>::Point() : _x(0), _y(0) {}

template<class T>
Point<T>::Point(T x, T y) : _x(x), _y(y) {}

template<class T>
Point<T>::Point(const Point<T>& other) {
    _x = other._x;
    _y = other._y;
}

template<class T>
void Point<T>::set_x(T x) {
    if (!isdigit(x)) throw std::logic_error("Not a number entered!");
    _x = x;
}

template<class T>
void Point<T>::set_y(T y) {
    if (!isdigit(y)) throw std::logic_error("Not a number entered!");
    _y = y;
}

template<class T>
T Point<T>::get_x() const { return _x; }

template<class T>
T Point<T>::get_y() const { return _y; }

template<class T>
std::ostream& operator<<(std::ostream& out, const Point<T>& point) {
    out << "(" << point._x << ", " << point._y << ")";
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, Point<T>& point) {
    in >> point._x >> point._y;
    return in;
}