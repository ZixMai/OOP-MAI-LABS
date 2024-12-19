#pragma once
#include "FigureArray.h"
#include <utility>

template <IsFigure T>
FigureArray<T>::FigureArray()
    : size_(0), capacity_(10), figures_(std::make_unique<std::shared_ptr<T>[]>(capacity_)) {};

template <IsFigure T>
FigureArray<T>::FigureArray(size_t capacity)
    : size_(0), capacity_(capacity), figures_(std::make_unique<std::shared_ptr<T>[]>(capacity_)) {}

template <IsFigure T>
FigureArray<T>::FigureArray(const FigureArray<T> &other)
    : size_(other.size_), capacity_(other.capacity_), figures_(std::make_unique<std::shared_ptr<T>[]>(other.capacity_))
{
    for (size_t i = 0; i < other.size_; ++i) {
        if (other.figures_[i]) {
            figures_[i] = other.figures_[i]->clone();
        } else {
            figures_[i] = nullptr;
        }
    }
    for (size_t i = other.size_; i < capacity_; ++i) {
        figures_[i] = nullptr;
    }
}

template <IsFigure T>
FigureArray<T>& FigureArray<T>::operator=(const FigureArray<T> &other)
{
    if (this == &other)
        return *this;

    auto newFigures = std::make_unique<std::shared_ptr<T>[]>(other.capacity_);
    for (size_t i = 0; i < other.size_; ++i) {
        if (other.figures_[i]) {
            newFigures[i] = other.figures_[i]->clone();
        } else {
            newFigures[i] = nullptr;
        }
    }

    for (size_t i = other.size_; i < other.capacity_; ++i) {
        newFigures[i] = nullptr;
    }
    figures_ = std::move(newFigures);
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}

template <IsFigure T>
FigureArray<T>::FigureArray(FigureArray<T> &&other) noexcept
    : size_(other.size_), capacity_(other.capacity_), figures_(std::move(other.figures_))
{
    other.size_ = 0;
    other.capacity_ = 0;
}

template <IsFigure T>
FigureArray<T>& FigureArray<T>::operator=(FigureArray<T> &&other) noexcept
{
    if (this != &other) {
        figures_ = std::move(other.figures_);
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <IsFigure T>
T& FigureArray<T>::operator[](size_t index) const
{
    return *figures_[index];
}

template <IsFigure T>
FigureArray<T>::~FigureArray() {}

template <IsFigure T>
void FigureArray<T>::add(const std::shared_ptr<T> &figure) {
    if (size_ >= capacity_) {
        resize();
    }
    figures_[size_++] = figure;
}

template <IsFigure T>
void FigureArray<T>::remove(size_t index)
{
    if (index >= size_) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }

    for (size_t i = index; i < size_ - 1; ++i) {
        figures_[i] = std::move(figures_[i + 1]);
    }
    figures_[size_ - 1] = nullptr;
    --size_;
}

template <IsFigure T>
double FigureArray<T>::totalArea() const
{
    double total = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        if (figures_[i]) {
            total += static_cast<double>(*figures_[i]);
        }
    }
    return total;
}

template <IsFigure T>
void FigureArray<T>::printAll() const
{
    for (size_t i = 0; i < size_; ++i) {
        if (figures_[i]) { 
            std::cout << *figures_[i] << std::endl;
        }
    }
}

template <IsFigure T>
size_t FigureArray<T>::size() const
{
    return size_;
}

template <IsFigure T>
void FigureArray<T>::resize()
{
    size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    auto newData = std::make_unique<std::shared_ptr<T>[]>(newCapacity);

    for (size_t i = 0; i < size_; ++i) {
        newData[i] = figures_[i];
    }

    for (size_t i = size_; i < newCapacity; ++i) {
        newData[i] = nullptr;
    }
    figures_ = std::move(newData);
    capacity_ = newCapacity;
}