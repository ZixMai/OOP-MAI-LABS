#pragma once
#include "Figure.h"
#include "Point.h"
#include <memory>
#include <iostream>
#include <stdexcept>

template <Numeric T>
class Trapezoid : public Figure<T> {
public:
    using figure_base_type = T;
    
    Trapezoid() = default;
    Trapezoid(const Point<T> (&points)[4]);
    Trapezoid(const Trapezoid<T> &other);

    Trapezoid& operator=(const Trapezoid<T> &other);
    Trapezoid& operator=(Trapezoid<T> &&other) noexcept;
    
    Point<T> geometricCenter() const override;
    operator double() const override;
    bool operator==(const Figure<T> &other) const override;

    virtual Figure<T>* clone() const override {
        return new Trapezoid(*this);
    }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

private:
    std::unique_ptr<Point<T>> points_[4];

    bool isValidTrapezoid() const;
};

#include "Trapezoid.tpp"