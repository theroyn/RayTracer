#include "math/vec3.h"

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

// vec3 Utility Functions

std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3& u, const vec3& v)
{
    return u + (-v);
}

vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator*(double t, const vec3& v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

vec3 operator+(double t, const vec3& v)
{
    return vec3(t + v.e[0], t + v.e[1], t + v.e[2]);
}

vec3 operator+(const vec3& v, double t)
{
    return t + v;
}

vec3 operator/(vec3 v, double t)
{
    return (1. / t) * v;
}

double dot(const vec3& u, const vec3& v)
{
    return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

vec3 cross(const vec3& u, const vec3& v)
{
    double resx = u.y() * v.z() - u.z() * v.y();
    double resy = u.z() * v.x() - u.x() * v.z();
    double resz = u.x() * v.y() - u.y() * v.x();
    return vec3(resx, resy, resz);
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

vec3 reflect(const vec3& v, const vec3& n)
{
    vec3 b = -dot(v, n) * n;
    vec3 reflection = v + 2.0 * b;

    return reflection;
}

vec3 refract(const vec3& unit_r, const vec3& n, double etai_over_etat)
{
    double cos_theta = fmin(-dot(unit_r, n), 1.);
    vec3 r_out_perp = etai_over_etat * (unit_r + cos_theta * n);
    vec3 r_out_par = -sqrt(fabs(1. - r_out_perp.length_squared())) * n;

    return r_out_perp + r_out_par;
}