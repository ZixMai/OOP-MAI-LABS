#include "Rhombus.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

template <Numeric T>
Rhombus<T>::Rhombus(const Point<T> (&points)[4])
{
    for (int i = 0; i < 4; ++i) {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!isValidRhombus()) {
        throw std::invalid_argument("Points do not form a valid rhombus.");
    }
}

template <Numeric T>
Rhombus<T>::Rhombus(const Rhombus<T> &other)
{
    for (int i = 0; i < 4; ++i) {
        if (other.points_[i]) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        } else {
            points_[i].reset();
        }
    }
    if (!isValidRhombus()) {
        throw std::invalid_argument("Invalid Rhombus points in copy constructor.");
    }
}

template <Numeric T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus<T> &other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < 4; ++i) {
        if (other.points_[i]) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        } else {
            points_[i].reset();
        }
    }

    if (!isValidRhombus()) {
        throw std::invalid_argument("Points do not form a valid rhombus after copy assignment.");
    }

    return *this;
}

template <Numeric T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus<T> &&other) noexcept
{
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points_[i] = std::move(other.points_[i]);
        }
    }
    return *this;
}

template <Numeric T>
Point<T> Rhombus<T>::geometricCenter() const
{
    double centerX = (points_[0]->x_ + points_[2]->x_) / 2.0;
    double centerY = (points_[0]->y_ + points_[2]->y_) / 2.0;

    return Point<T>(centerX, centerY);
}

template <Numeric T>
double Rhombus<T>::distance(const Point<T> &p1, const Point<T> &p2) const {
    double dx = static_cast<double>(p2.x_) - static_cast<double>(p1.x_);
    double dy = static_cast<double>(p2.y_) - static_cast<double>(p1.y_);

    return std::sqrt(dx * dx + dy * dy);
}

template <Numeric T>
Rhombus<T>::operator double() const
{
    double d1 = distance(*points_[0], *points_[2]);
    double d2 = distance(*points_[1], *points_[3]);

    return 0.5 * d1 * d2;
}

template <Numeric T>
bool Rhombus<T>::operator==(const Figure<T> &other) const
{
    const Rhombus<T>* otherRhombus = dynamic_cast<const Rhombus<T>*>(&other);
    if (!otherRhombus)
        return false;

    for (int i = 0; i < 4; ++i) {
        if (*(points_[i]) != *(otherRhombus->points_[i])) {
            return false;
        }
    }
    return true;
}

template <Numeric T>
void Rhombus<T>::print(std::ostream& os) const
{
    os << "Rhombus: points = ";
    for (int i = 0; i < 4; ++i) {
        os << *(points_[i]) << " ";
    }
}

template <Numeric T>
void Rhombus<T>::read(std::istream& is)
{
    Point<T> tempPoints[4];
    for (int i = 0; i < 4; ++i) {
        is >> tempPoints[i];
    }
    for (int i = 0; i < 4; ++i) {
        points_[i] = std::make_unique<Point<T>>(tempPoints[i]);
    }

    if (!isValidRhombus()) {
        throw std::invalid_argument("Points do not form a valid rhombus after reading.");
    }
}

template <Numeric T>
bool Rhombus<T>::isValidRhombus() const
{
    const double epsilon = 1e-3;
    double sideLength = distance(*points_[0], *points_[1]);

    for (int i = 1; i < 4; ++i) {
        int next = (i + 1) % 4;
        double currentSide = distance(*points_[i], *points_[next]);
        if (std::abs(currentSide - sideLength) > epsilon) {
            return false;
        }
    }

    return true;
}