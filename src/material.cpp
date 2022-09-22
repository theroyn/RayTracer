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
    vec3 b = -dot(in.direction(), rec.normal) * rec.normal;
    vec3 reflection = in.direction() + 2.0 * b + _fuzziness * vec3::random_in_unit_sphere();
    scattered = ray(rec.p, reflection);
    attenuation = _albedo;

    return true;
}