#include "math/vec3.hpp"

double vec3::x() const
{
    return e[0];
}

double vec3::y() const
{
    return e[1];
}

double vec3::z() const
{
    return e[2];
}

vec3 vec3::operator-() const
{
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int idx) const
{
    return e[idx];
}

double& vec3::operator[](int idx)
{
    return e[idx];
}

vec3& vec3::operator+=(const vec3& v)
{
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];

    return *this;
}

vec3& vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

vec3& vec3::operator/=(const double t)
{
    double inv = 1. / t;

    return *this *= inv;
}

double vec3::length() const
{
    return std::sqrt(length_squared());
}

double vec3::length_squared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

bool vec3::near_zero() const
{
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

vec3 vec3::random(double min, double max)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 vec3::random_in_unit_sphere()
{
    vec3 random_in_unit_square = vec3::random();
    while (random_in_unit_square.length_squared() >= 1)
    {
        random_in_unit_square = vec3::random();
    }

    return random_in_unit_square;
}

vec3 vec3::random_on_surface_of_unit_sphere()
{
    return unit_vector(random_in_unit_sphere());
}

vec3 vec3::random_in_hemisphere(const vec3& normal)
{
    vec3 v = random_in_unit_sphere();

    if (dot(v, normal) >= 0.)
    {
        return v;
    }
    else
    {
        return -v;
    }
}

vec3 vec3::random_in_unit_disk()
{
    vec3 random_in_unit_square = vec3(random_double(-1., 1.), random_double(-1., 1.), 0.);
    while (random_in_unit_square.length_squared() >= 1)
    {
        random_in_unit_square = vec3(random_double(), random_double(), 0.);
    }

    return random_in_unit_square;
}