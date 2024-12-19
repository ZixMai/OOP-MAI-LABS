#include "Rhombus.h"
#include <cmath>
#include <iostream>

Rhombus::Rhombus(const Point (&points)[4])
{
    for (int i = 0; i < 4; ++i) {
        points_[i] = points[i];
    }
    if (!isValidRhombus()) {
        throw std::invalid_argument("Points do not form a valid rhombus.");
    }
}

Rhombus::Rhombus(const Rhombus& other) {
    for (int i = 0; i < 4; ++i) {
        points_[i] = other.points_[i];
    }
}

Rhombus &Rhombus::operator=(const Rhombus &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            points_[i] = other.points_[i];
        }
    }
    return *this;
}

Rhombus &Rhombus::operator=(Rhombus &&other) noexcept
{
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            points_[i] = std::move(other.points_[i]);
        }
    }
    return *this;
}

Point Rhombus::geometricCenter() const
{
    double centerX = (points_[0].x_ + points_[2].x_) / 2.0;
    double centerY = (points_[0].y_ + points_[2].y_) / 2.0;

    return Point{centerX, centerY};
}

double Rhombus::distance(const Point &p1, const Point &p2) const {
    double dx = p2.x_ - p1.x_;
    double dy = p2.y_ - p1.y_;
    return std::sqrt(dx * dx + dy * dy);
}

Rhombus::operator double() const
{
    double d1 = distance(points_[0], points_[2]);
    double d2 = distance(points_[1], points_[3]);
    return 0.5 * d1 * d2;
}

bool Rhombus::operator==(const Figure &other) const
{
    const Rhombus *otherRhombus = dynamic_cast<const Rhombus *>(&other);
    if (!otherRhombus)
        return false;
    for (int i = 0; i < 4; ++i)
    {
        if (points_[i] != otherRhombus->points_[i])
        {
            return false;
        }
    }
    return true;
}

void Rhombus::print(std::ostream& os) const
{
    os << "Rhombus: points = ";
    for (const auto &point : points_)
    {
        os << point << " ";
    }
}

void Rhombus::read(std::istream& is)
{
    Point points[4];
    for (int i = 0; i < 4; ++i)
    {
        is >> points[i];
    }
    for (int i = 0; i < 4; ++i)
    {
        points_[i] = points[i];
    }
}

bool Rhombus::isValidRhombus() const
{
    const double epsilon = 1e-3;
    double sideLength = std::sqrt(std::pow(points_[1].x_ - points_[0].x_, 2) + std::pow(points_[1].y_ - points_[0].y_, 2));

    for (int i = 1; i < 4; ++i) {
        int next = (i + 1) % 4;
        double currentSide = std::sqrt(std::pow(points_[next].x_ - points_[i].x_, 2) + std::pow(points_[next].y_ - points_[i].y_, 2));
        if (std::abs(currentSide - sideLength) > epsilon) {
            throw std::invalid_argument("Points do not form a valid rhombus.");
        }
    }

    return true;
}
