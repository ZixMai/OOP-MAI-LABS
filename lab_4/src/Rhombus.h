#pragma once
#include "Figure.h"
#include "Point.h"
#include <memory>
#include <iostream>
#include <stdexcept>

template <Numeric T>
class Rhombus : public Figure<T> {
public:
    using figure_base_type = T;
    
    Rhombus() = default;
    Rhombus(const Point<T> (&points)[4]);
    Rhombus(const Rhombus<T> &other);

    Rhombus &operator=(const Rhombus<T> &other);
    Rhombus &operator=(Rhombus<T> &&other) noexcept;

    Point<T> geometricCenter() const override;
    double distance(const Point<T> &p1, const Point<T> &p2) const;
    operator double() const override;
    bool operator==(const Figure<T> &other) const override;

    virtual Figure<T>* clone() const override {
        return new Rhombus(*this);
    }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

private:
    std::unique_ptr<Point<T>> points_[4];

    bool isValidRhombus() const;
};

#include "Rhombus.tpp"