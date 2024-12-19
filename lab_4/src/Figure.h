#pragma once
#include "Point.h"
#include <iostream>

template <Numeric T>
class Figure {
public:
    virtual ~Figure() noexcept = default;

    virtual Point<T> geometricCenter() const = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure<T> &other) const = 0;

    virtual Figure* clone() const = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
};

template <Numeric T>
std::ostream& operator<<(std::ostream& os, const Figure<T> &fig);

template <Numeric T>
std::istream& operator>>(std::istream& is, Figure<T> &fig);

#include "Figure.tpp"