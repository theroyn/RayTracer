#pragma once

#include "math/common.hpp"

#include <cmath>
#include <ostream>

class vec3
{
public:
    vec3() : e{ 0., 0., 0. } {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);

    vec3& operator*=(const double t);

    vec3& operator/=(const double t);

    double length() const;

    double length_squared() const;

    // will actually be inside unit cube [0,1] x [0,1] x [0,1]
    static vec3 random();

    static vec3 random_in_unit_sphere();
    static vec3 random_on_surface_of_unit_sphere();
    static vec3 random_in_hemisphere(const vec3& normal);

public:
    double e[3];
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return u + (-v);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

inline vec3 operator+(double t, const vec3& v)
{
    return vec3(t + v.e[0], t + v.e[1], t + v.e[2]);
}

inline vec3 operator+(const vec3& v, double t)
{
    return t + v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1. / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
    return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

inline vec3 cross(const vec3& u, const vec3& v)
{
    double resx = u.y() * v.z() - u.z() * v.y();
    double resy = u.z() * v.x() - u.x() * v.z();
    double resz = u.x() * v.y() - u.y() * v.x();
    return vec3(resx, resy, resz);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}