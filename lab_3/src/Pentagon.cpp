#include "Pentagon.h"
#include <cmath>
#include <iostream>

Pentagon::Pentagon(const Point (&points)[5])
{
    for (int i = 0; i < 5; ++i) {
        points_[i] = points[i];
    }
}

Pentagon::Pentagon(const Pentagon &other)
{
    for (int i = 0; i < 5; ++i) {
        points_[i] = other.points_[i];
    }
}

Pentagon& Pentagon::operator=(const Pentagon &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 5; ++i)
        {
            points_[i] = other.points_[i];
        }
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon &&other) noexcept
{
    if (this != &other)
    {
        for (int i = 0; i < 5; ++i)
        {
            points_[i] = std::move(other.points_[i]);
        }
    }
    return *this;
}

Point Pentagon::geometricCenter() const
{
    double centerX = 0, centerY = 0;
    for (const auto &point : points_)
    {
        centerX += point.x_;
        centerY += point.y_;
    }
    return Point{centerX / 5, centerY / 5};
}

Pentagon::operator double() const
{
    double area = 0;
    for (int i = 0; i < 5; ++i)
    {
        int j = (i + 1) % 5;
        area += points_[i].x_ * points_[j].y_ - points_[j].x_ * points_[i].y_;
    }
    return std::abs(area) / 2;
}

bool Pentagon::operator==(const Figure &other) const
{
    const Pentagon *otherPentagon = dynamic_cast<const Pentagon *>(&other);
    if (!otherPentagon)
        return false;
    for (int i = 0; i < 5; ++i)
    {
        if (points_[i] != otherPentagon->points_[i])
        {
            return false;
        }
    }
    return true;
}

void Pentagon::print(std::ostream& os) const
{
    os << "Pentagon: points = ";
    for (const auto &point : points_)
    {
        os << point << " ";
    }
}

void Pentagon::read(std::istream& is)
{
    Point points[5];
    for (int i = 0; i < 5; ++i)
    {
        is >> points[i];
    }
    for (int i = 0; i < 5; ++i)
    {
        points_[i] = points[i];
    }
}

bool Pentagon::isValidPentagon() const
{
    const double epsilon = 1e-3;
    double sideLength = std::sqrt(std::pow(points_[1].x_ - points_[0].x_, 2) + std::pow(points_[1].y_ - points_[0].y_, 2));

    for (int i = 1; i < 5; ++i) {
        int next = (i + 1) % 5;
        double currentSide = std::sqrt(std::pow(points_[next].x_ - points_[i].x_, 2) + std::pow(points_[next].y_ - points_[i].y_, 2));
        if (std::abs(currentSide - sideLength) > epsilon) {
            throw std::invalid_argument("Points do not form a valid pentagon.");
        }
    }

    return true;
}
