#pragma once
#include "Point.h"

template <Numeric T>
std::ostream &operator<<(std::ostream& os, const Point<T> &point)
{
    os << "(" << point.x_ << ", " << point.y_ << ")";
    return os;
}

template <Numeric T>
std::istream &operator>>(std::istream& is, Point<T> &point)
{
    is >> point.x_ >> point.y_;
    return is;
}

template <Numeric T>
bool Point<T>::operator==(const Point<T> &other) const
{
    return std::abs(x_ - other.x_) < 1e-6 && std::abs(y_ - other.y_) < 1e-6;
}

template <Numeric T>
bool Point<T>::operator!=(const Point<T> &other) const
{
    return !(*this == other);
}