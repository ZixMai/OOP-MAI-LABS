#pragma once
#include <iostream>
#include <cmath>

template <class T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <Numeric T>
struct Point {
    T x_;
    T y_;

    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}

    bool operator==(const Point<T> &other) const;
    bool operator!=(const Point<T> &other) const;
};

template <Numeric T>
std::ostream &operator<<(std::ostream& os, const Point<T>& point);

template <Numeric T>
std::istream &operator>>(std::istream& is, Point<T>& point);

#include "Point.tpp"