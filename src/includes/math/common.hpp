#pragma once

static inline constexpr double pi = 3.1415926535897932385;

double degrees_to_rad(double deg)
{
    return deg * pi / 180.;
}