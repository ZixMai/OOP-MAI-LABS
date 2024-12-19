#pragma once
#include "Figure.h"

template <Numeric T>
std::ostream& operator<<(std::ostream& os, const Figure<T> &fig)
{
    fig.print(os);
    return os;
}

template <Numeric T>
std::istream& operator>>(std::istream& is, Figure<T> &fig)
{
    fig.read(is);
    return is;
}