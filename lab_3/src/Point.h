#pragma once
#include <iostream>
#include <cmath>

struct Point
{
    double x_;
    double y_;

    Point() : x_(0), y_(0) {}
    Point(double x, double y) : x_(x), y_(y) {}

    friend std::ostream &operator<<(std::ostream& os, const Point &point)
    {
        os << "(" << point.x_ << ", " << point.y_ << ")";
        return os;
    }
    friend std::istream &operator>>(std::istream& is, Point &point)
    {
        is >> point.x_ >> point.y_;
        return is;
    }

    bool operator==(const Point &other) const
    {
        return std::abs(x_ - other.x_) < 1e-6 && std::abs(y_ - other.y_) < 1e-6;
    }
    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }
};
