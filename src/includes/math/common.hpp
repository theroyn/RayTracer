#pragma once

#include <limits>
#include <random>

static inline constexpr double infinity = std::numeric_limits<double>::infinity();

static inline constexpr double pi = 3.1415926535897932385;

inline double degrees_to_rad(double deg)
{
    return deg * pi / 180.;
}

inline double random_double(double min = 0., double max = 1.)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;

    return x;
}
