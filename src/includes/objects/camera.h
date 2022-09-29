#pragma once

#include "math/ray.h"

class camera
{
public:
    camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist);

    ray get_ray(double s, double t) const;

private:
    point3 _origin;
    point3 _lower_left_corner;
    vec3 _horizontal;
    vec3 _vertical;
    double _lens_rad;
};