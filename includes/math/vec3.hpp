#pragma once

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

public:
    double e[3];
};

inline double vec3::x() const
{
    return e[0];
}

inline double vec3::y() const
{
    return e[1];
}

inline double vec3::z() const
{
    return e[2];
}

inline vec3 vec3::operator-() const
{
    return vec3(-e[0], -e[1], -e[2]);
}

inline double vec3::operator[](int idx) const
{
    return e[idx];
}

inline double& vec3::operator[](int idx)
{
    return e[idx];
}

inline vec3& vec3::operator+=(const vec3& v)
{
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];

    return *this;
}

inline vec3& vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

inline vec3& vec3::operator/=(const double t)
{
    double inv = 1. / t;

    return *this *= inv;
}

inline double vec3::length() const
{
    return std::sqrt(length_squared());
}

inline double vec3::length_squared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

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