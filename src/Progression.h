#pragma once

#include "Progress.h"

#include <array>

class LinearProgression : public Progression
{
  public:
    LinearProgression(int size) : max_size(size) {}

    virtual ~LinearProgression() = default;

    void setValue(int value) { curr_value = value; }

    float percentage() const override
    {
        return static_cast<float>(curr_value) / max_size;
    }

  private:
    int curr_value = 0;
    int max_size = 0;
};

template <int N> class MultiDimensionalProgression : public Progression
{
  public:
    MultiDimensionalProgression(std::array<int, N> &&sizes)
        : max_sizes(std::move(sizes))
    {
        static_assert(N > 1, "Use LinearProgression instead");

        double max = 1.0;
        double factor = 1.0;
        for (int i = N - 1; i >= 0; i--)
        {
            if (i < N - 1)
            {
                factor *= max_sizes[i + 1];
            }
            factors[i] = factor;
            max *= max_sizes[i];
        }
        max_value = max;
    }

    virtual ~MultiDimensionalProgression() = default;

    void setValue(std::array<int, N> value) { curr_value = value; }

    float percentage() const override
    {
        double p = 0;
        for (int i = 0; i < N; i++)
        {
            p += curr_value[i] * factors[i];
        }
        return static_cast<float>(p / max_value);
    }

  private:
    std::array<int, N> max_sizes;
    double max_value{0};
    std::array<int, N> curr_value;
    std::array<double, N> factors;
};

using BiLinearProgression = MultiDimensionalProgression<2>;
using TriLinearProgression = MultiDimensionalProgression<3>;
