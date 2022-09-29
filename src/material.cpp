#include "objects/material.h"

bool lambertian::scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 ray_direction = rec.normal + vec3::random_on_surface_of_unit_sphere();

    // Catch degenerate scatter direction
    if (ray_direction.near_zero())
        ray_direction = rec.normal;

    scattered = ray(rec.p, ray_direction);
    attenuation = _albedo;

    return true;
}

bool metal::scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 reflection = reflect(in.direction(), rec.normal);
    scattered = ray(rec.p, reflection + _fuzziness * vec3::random_in_unit_sphere());
    attenuation = _albedo;

    return true;
}

bool dielectric::scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    static constexpr double eta_air = 1.0;
    double refraction_ratio = rec.front_face ? eta_air / _ir : _ir;
    vec3 unit_in_dir = unit_vector(in.direction());

    double cos_theta = fmin(-dot(unit_in_dir, rec.normal), 1.);
    double sine_theta = sqrt(1. - cos_theta * cos_theta);

    bool cannot_refract = (refraction_ratio * sine_theta > 1.);
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
    {
        vec3 reflection = reflect(unit_in_dir, rec.normal);
        scattered = ray(rec.p, reflection);
    }
    else
    {
        vec3 refraction = refract(unit_in_dir, rec.normal, refraction_ratio);
        scattered = ray(rec.p, refraction);
    }

    attenuation = color(1.);
    return true;
}

double dielectric::reflectance(double cos_theta, double refraction_ratio)
{
    // Use Schlick's approximation for reflectance.
    double r0 = (1. - refraction_ratio) / (1. + refraction_ratio);
    r0 = r0 * r0;
    return r0 + (1. - r0) * pow((1. - cos_theta), 5);
}