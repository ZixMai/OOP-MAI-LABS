#pragma once
#include "Figure.h"
#include "Point.h"
#include <memory>
#include <iostream>
#include <stdexcept>

template <Numeric T>
class Pentagon : public Figure<T> {
public:
    using figure_base_type = T;

    Pentagon() = default;
    Pentagon(const Point<T> (&points)[5]);
    Pentagon(const Pentagon<T> &other);

    Pentagon& operator=(const Pentagon<T> &other);
    Pentagon& operator=(Pentagon<T> &&other) noexcept;

    Point<T> geometricCenter() const override;
    operator double() const override;
    bool operator==(const Figure<T> &other) const override;

    virtual Figure<T>* clone() const override {
        return new Pentagon(*this);
    }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

private:
    std::unique_ptr<Point<T>> points_[5];
    
    bool isValidPentagon() const;
};

#include "Pentagon.tpp"