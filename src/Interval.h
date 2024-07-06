#pragma once

#include <limits>

template <typename T> class IntervalT
{
  public:
    IntervalT() = default;

    IntervalT(T _min, T _max) : min(_min), max(_max) {}

    static IntervalT toForwardInfinity(T min)
    {
        return IntervalT{min, std::numeric_limits<T>::infinity()};
    }

    static IntervalT toBackwardInfinity(T max)
    {
        return IntervalT{-std::numeric_limits<T>::infinity(), max};
    }

    T min{std::numeric_limits<T>::infinity()};
    T max{-std::numeric_limits<T>::infinity()};

    bool contains(const T &value) const { return min <= value && value <= max; }

    bool excludes(const T &value) const { return value < min || value > max; }

    bool surrounds(const T &value) const { return min < value && value < max; }

    T clamp(const T &value) const
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    static const IntervalT empty;
    static const IntervalT universe;
    static const IntervalT forwardInfinite;
    static const IntervalT backInfinite;
};

template <typename T> const IntervalT<T> IntervalT<T>::empty = IntervalT{};

template <typename T>
const IntervalT<T> IntervalT<T>::universe = IntervalT{
    -std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()};

template <typename T>
const IntervalT<T> IntervalT<T>::forwardInfinite =
    IntervalT{0, std::numeric_limits<T>::infinity()};

template <typename T>
const IntervalT<T> IntervalT<T>::backInfinite =
    IntervalT{-std::numeric_limits<T>::infinity(), 0};

using Interval = IntervalT<float>;
