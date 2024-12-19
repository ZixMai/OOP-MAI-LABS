#pragma once
#include "Figure.h"

class FigureArray 
{
public:
    FigureArray(size_t capacity);
    FigureArray(const FigureArray &other);

    FigureArray& operator=(const FigureArray &other);
    FigureArray& operator=(FigureArray &&other) noexcept;
    FigureArray(FigureArray &&other) noexcept;

    ~FigureArray();

    void add(Figure *figure);
    void remove(size_t index);
    double totalArea() const;
    void printAll() const;
    size_t size() const;

private:
    Figure **figures_;
    size_t size_;
    size_t capacity_;

    void resize();
};
