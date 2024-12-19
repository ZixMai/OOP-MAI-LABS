#pragma once
#include "Point.h"
#include <iostream>

class Figure
{
public:
    virtual Point geometricCenter() const = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure &other) const = 0;
    virtual Figure* clone() const = 0;
    virtual ~Figure() noexcept = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure &fig) {
        fig.print(os);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Figure &fig) {
        fig.read(is);
        return is;
    }
};
