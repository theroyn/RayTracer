#pragma once

#include "math/ray.h"

class camera
{
public:
    camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio) : _origin(0., 0., 0.)
    {
        double theta = degrees_to_rad(vfov);
        double h = tan(theta * .5);
        double viewport_height = 2. * h;
        double viewport_width = viewport_height * aspect_ratio;

        _origin = lookfrom;

        vec3 w = unit_vector(lookfrom - lookat);
        vec3 u = unit_vector(cross(vup, w));
        vec3 v = cross(w, u);

        _horizontal = viewport_width * u;
        _vertical = viewport_height * v;

        _lower_left_corner = _origin - _horizontal * .5 - _vertical * .5 - w;
    }

    ray get_ray(double u, double v) const
    {
        return ray(_origin, _lower_left_corner + u * _horizontal + v * _vertical - _origin);
    }

private:
    point3 _origin;
    point3 _lower_left_corner;
    vec3 _horizontal;
    vec3 _vertical;
};