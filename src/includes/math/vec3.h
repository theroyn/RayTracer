#pragma once

#include "math/common.hpp"

#include <cmath>
#include <ostream>

class vec3
{
public:
    vec3() : e{ 0., 0., 0. } {}
    vec3(double e) : e{ e, e, e } {}
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

    bool near_zero() const;

    // will actually be inside unit cube [0,1] x [0,1] x [0,1]
    static vec3 random(double min = 0., double max = 1.);

    static vec3 random_in_unit_sphere();
    static vec3 random_on_surface_of_unit_sphere();
    static vec3 random_in_hemisphere(const vec3& normal);
    static vec3 random_in_unit_disk();

public:
    double e[3];
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

// vec3 Utility Functions

std::ostream& operator<<(std::ostream& out, const vec3& v);

vec3 operator+(const vec3& u, const vec3& v);

vec3 operator-(const vec3& u, const vec3& v);

vec3 operator*(const vec3& u, const vec3& v);

vec3 operator*(double t, const vec3& v);

vec3 operator*(const vec3& v, double t);

vec3 operator+(double t, const vec3& v);

vec3 operator+(const vec3& v, double t);

vec3 operator/(vec3 v, double t);

double dot(const vec3& u, const vec3& v);

vec3 cross(const vec3& u, const vec3& v);

vec3 unit_vector(vec3 v);

vec3 reflect(const vec3& v, const vec3& n);

vec3 refract(const vec3& unit_r, const vec3& n, double etai_over_etat);