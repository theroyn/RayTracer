#pragma once

#include "math/ray.h"

class camera
{
public:
    camera(double aspect_ratio) : _origin(0., 0., 0.)
    {
        double viewport_height = 2.;
        double viewport_width = viewport_height * aspect_ratio;
        double focal_length = 1.;

        _horizontal = vec3(viewport_width, 0., 0.);
        _vertical = vec3(0., viewport_height, 0.);

        _lower_left_corner = _origin - _horizontal * .5 - _vertical * .5 - vec3(0., 0., focal_length);
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