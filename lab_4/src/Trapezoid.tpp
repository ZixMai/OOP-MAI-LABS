#pragma once
#include "Trapezoid.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

template <Numeric T>
Trapezoid<T>::Trapezoid(const Point<T> (&points)[4])
{
    for (int i = 0; i < 4; ++i) {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!isValidTrapezoid()) {
        throw std::invalid_argument("Points do not form a valid trapezoid.");
    }
}

template <Numeric T>
Trapezoid<T>::Trapezoid(const Trapezoid<T> &other)
{
    for (int i = 0; i < 4; ++i) {
        if (other.points_[i]) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        } else {
            points_[i].reset();
        }
    }
    if (!isValidTrapezoid()) {
        throw std::invalid_argument("Invalid Trapezoid points in copy constructor.");
    }
}

template <Numeric T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T> &other)
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

    if (!isValidTrapezoid()) {
        throw std::invalid_argument("Invalid Trapezoid points after copy assignment.");
    }

    return *this;
}

template <Numeric T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid<T> &&other) noexcept
{
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points_[i] = std::move(other.points_[i]);
        }
    }
    return *this;
}

template <Numeric T>
Point<T> Trapezoid<T>::geometricCenter() const
{
    double centerX = 0, centerY = 0;
    for (const auto &point : points_) {
        centerX += point->x_;
        centerY += point->y_;
    }
    return Point<T>(centerX / 4.0, centerY / 4.0);
}

template <Numeric T>
Trapezoid<T>::operator double() const
{
    double area = 0.0;
    for (int i = 0; i < 4; ++i) {
        const auto& p1 = points_[i];
        const auto& p2 = points_[(i + 1) % 4];

        area += (p1->x_ * p2->y_ - p2->x_ * p1->y_);
    }
    return std::abs(area) / 2.0;
}

template <Numeric T>
bool Trapezoid<T>::operator==(const Figure<T> &other) const
{
    const Trapezoid<T>* otherTrapezoid = dynamic_cast<const Trapezoid<T>*>(&other);
    if (!otherTrapezoid)
        return false;

    for (int i = 0; i < 4; ++i) {
        if (*(points_[i]) != *(otherTrapezoid->points_[i])) {
            return false;
        }
    }
    return true;
}

template <Numeric T>
void Trapezoid<T>::print(std::ostream& os) const
{
    os << "Trapezoid: points = ";
    for (int i = 0; i < 4; ++i) {
        os << *(points_[i]) << " ";
    }
}

template <Numeric T>
void Trapezoid<T>::read(std::istream& is)
{
    Point<T> tempPoints[4];
    for (int i = 0; i < 4; ++i) {
        is >> tempPoints[i];
    }
    for (int i = 0; i < 4; ++i) {
        points_[i] = std::make_unique<Point<T>>(tempPoints[i]);
    }

    if (!isValidTrapezoid()) {
        throw std::invalid_argument("Points do not form a valid trapezoid after reading.");
    }
}

template <Numeric T>
bool Trapezoid<T>::isValidTrapezoid() const
{
    double epsilon = 1e-6;
    
    auto calculateSlope = [&](const Point<T> &p1, const Point<T> &p2) -> double {
        if (std::abs(p2.x_ - p1.x_) < epsilon) {
            return std::numeric_limits<double>::infinity();
        }
        return (static_cast<double>(p2.y_) - static_cast<double>(p1.y_)) / (static_cast<double>(p2.x_) - static_cast<double>(p1.x_));
    };
    
    double slope1 = calculateSlope(*points_[0], *points_[1]);
    double slope2 = calculateSlope(*points_[2], *points_[3]);
    double slope3 = calculateSlope(*points_[1], *points_[2]);
    double slope4 = calculateSlope(*points_[3], *points_[0]);

    bool pair1Parallel = (std::isinf(slope1) && std::isinf(slope2)) ||
                         (std::abs(slope1 - slope2) <= epsilon);
    bool pair2Parallel = (std::isinf(slope3) && std::isinf(slope4)) ||
                         (std::abs(slope3 - slope4) <= epsilon);
    
    if (pair1Parallel || pair2Parallel) {
        return true;
    } else {
        return false;
    }
}