#pragma once
#include "Pentagon.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

template <Numeric T>
Pentagon<T>::Pentagon(const Point<T> (&points)[5])
{
    for (int i = 0; i < 5; ++i) {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!isValidPentagon()) {
        throw std::invalid_argument("Invalid Pentagon points.");
    }
}

template <Numeric T>
Pentagon<T>::Pentagon(const Pentagon<T> &other)
{
    for (int i = 0; i < 5; ++i) {
        if (other.points_[i]) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        } else {
            points_[i].reset();
        }
    }
    if (!isValidPentagon()) {
        throw std::invalid_argument("Invalid Pentagon points in copy constructor.");
    }
}

template <Numeric T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T> &other)   
{
    if (this != &other) {
        for (int i = 0; i < 5; ++i) {
            if (other.points_[i]) {
                points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
            } else {
                points_[i].reset();
            }
        }
        if (!isValidPentagon()) {
            throw std::invalid_argument("Invalid Pentagon points in copy assignment.");
        }
    }
    return *this;
}

template <Numeric T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T> &&other) noexcept
{
    if (this != &other) {
        for (int i = 0; i < 5; ++i) {
            points_[i] = std::move(other.points_[i]);
        }
    }
    return *this;
}

template <Numeric T>
Point<T> Pentagon<T>::geometricCenter() const
{
    double centerX = 0, centerY = 0;
    for (int i = 0; i < 5; ++i) {
        centerX += points_[i]->x_;
        centerY += points_[i]->y_;
    }
    return Point<T>(centerX / 5, centerY / 5);
}

template <Numeric T>
Pentagon<T>::operator double() const
{
    double area = 0;
    for (int i = 0; i < 5; ++i) {
        int j = (i + 1) % 5;
        area += points_[i]->x_ * points_[j]->y_ - points_[j]->x_ * points_[i]->y_;
    }
    return std::abs(area) / 2;
}

template <Numeric T>
bool Pentagon<T>::operator==(const Figure<T> &other) const
{
    const Pentagon<T>* otherPentagon = dynamic_cast<const Pentagon<T>*>(&other);
    if (!otherPentagon)
        return false;

    for (int i = 0; i < 5; ++i) {
        if (*(points_[i]) != *(otherPentagon->points_[i])) {
            return false;
        }
    }
    return true;
}

template <Numeric T>
void Pentagon<T>::print(std::ostream& os) const
{
    os << "Pentagon: points = ";
    for (int i = 0; i < 5; ++i) {
        os << *(points_[i]) << " ";
    }
}

template <Numeric T>
void Pentagon<T>::read(std::istream& is)
{
    Point<T> tempPoints[5];
    for (int i = 0; i < 5; ++i) {
        is >> tempPoints[i];
    }
    for (int i = 0; i < 5; ++i) {
        points_[i] = std::make_unique<Point<T>>(tempPoints[i]);
    }
    if (!isValidPentagon()) {
        throw std::invalid_argument("Invalid Pentagon points after reading.");
    }

}

template <Numeric T>
bool Pentagon<T>::isValidPentagon() const
{
    const double epsilon = 1e-3;
    double sideLength = std::sqrt(std::pow(points_[1]->x_ - points_[0]->x_, 2) + std::pow(points_[1]->y_ - points_[0]->y_, 2));

    for (int i = 1; i < 5; ++i) {
        int next = (i + 1) % 5;
        double currentSide = std::sqrt(std::pow(points_[next]->x_ - points_[i]->x_, 2) + std::pow(points_[next]->y_ - points_[i]->y_, 2));
        if (std::abs(currentSide - sideLength) > epsilon) {
            return false;
        }
    }

    return true;
}