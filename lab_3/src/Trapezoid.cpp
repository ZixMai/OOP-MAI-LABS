#include "Trapezoid.h"
#include <cmath>
#include <limits>
#include <iostream>

Trapezoid::Trapezoid(const Point (&points)[4])
{
    for (int i = 0; i < 4; ++i) {
        points_[i] = points[i];
    }
    if (!isValidTrapezoid()) {
        throw std::invalid_argument("Points do not form a valid trapezoid.");
    }
}

Trapezoid::Trapezoid(const Trapezoid &other)
{
    for (int i = 0; i < 4; ++i) {
        points_[i] = other.points_[i];
    }
}

Trapezoid& Trapezoid::operator=(const Trapezoid &other)
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

Trapezoid& Trapezoid::operator=(Trapezoid &&other) noexcept
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

Point Trapezoid::geometricCenter() const
{
    double centerX = 0, centerY = 0;
    for (const auto &point : points_)
    {
        centerX += point.x_;
        centerY += point.y_;
    }
    return Point{centerX / 4, centerY / 4};
}

Trapezoid::operator double() const
{
    double area = 0.0;
    for (int i = 0; i < 4; ++i) {
        const auto& p1 = points_[i];
        const auto& p2 = points_[(i + 1) % 4];
        area += (p1.x_ * p2.y_ - p2.x_ * p1.y_);
    }
    return std::abs(area) / 2.0;
}

bool Trapezoid::operator==(const Figure &other) const
{
    const Trapezoid *otherTrapezoid = dynamic_cast<const Trapezoid *>(&other);
    if (!otherTrapezoid)
        return false;
    for (int i = 0; i < 4; ++i)
    {
        if (points_[i] != otherTrapezoid->points_[i])
        {
            return false;
        }
    }
    return true;
}

void Trapezoid::print(std::ostream& os) const
{
    os << "Trapezoid: points = ";
    for (const auto &point : points_) {
        os << point << " ";
    }
}

void Trapezoid::read(std::istream& is)
{
    Point points[4];
    for (int i = 0; i < 4; ++i) {
        is >> points[i];
    }
    for (int i = 0; i < 4; ++i) {
        points_[i] = points[i];
    }
}

bool Trapezoid::isValidTrapezoid() const
{
    double epsilon = 1e-6;
    
    auto calculateSlope = [&](const Point &p1, const Point &p2) -> double {
        if (std::abs(p2.x_ - p1.x_) < epsilon) {
            return std::numeric_limits<double>::infinity();
        }
        return (p2.y_ - p1.y_) / (p2.x_ - p1.x_);
    };
    
    double slope1 = calculateSlope(points_[0], points_[1]);
    double slope2 = calculateSlope(points_[2], points_[3]);
    double slope3 = calculateSlope(points_[1], points_[2]);
    double slope4 = calculateSlope(points_[3], points_[0]);

    bool pair1Parallel = (std::isinf(slope1) && std::isinf(slope2)) ||
                         (std::abs(slope1 - slope2) <= epsilon);
    bool pair2Parallel = (std::isinf(slope3) && std::isinf(slope4)) ||
                         (std::abs(slope3 - slope4) <= epsilon);
    
    if (pair1Parallel || pair2Parallel) { return true; }
    throw std::invalid_argument("Points do not form a valid trapezoid.");
}
