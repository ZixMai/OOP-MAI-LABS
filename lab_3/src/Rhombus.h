#pragma once
#include "Figure.h"
#include "Point.h"

class Rhombus : public Figure
{
public:
    Rhombus() = default;
    Rhombus(const Point (&points)[4]);
    Rhombus(const Rhombus &other);

    Rhombus &operator=(const Rhombus &other);
    Rhombus &operator=(Rhombus &&other) noexcept;

    Point geometricCenter() const override;
    double distance(const Point &p1, const Point &p2) const;
    operator double() const override;
    bool operator==(const Figure &other) const override;

    virtual Figure* clone() const override {
        return new Rhombus(*this);
    }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

private:
    Point points_[4];

    bool isValidRhombus() const;
};
