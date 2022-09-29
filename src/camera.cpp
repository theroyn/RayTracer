#include "objects/camera.h"

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist)
    : _origin(0., 0., 0.)
{
    double theta = degrees_to_rad(vfov);
    double h = tan(theta * .5);
    double viewport_height = 2. * h;
    double viewport_width = viewport_height * aspect_ratio;

    _origin = lookfrom;

    vec3 forward = unit_vector(lookfrom - lookat);
    vec3 right = unit_vector(cross(vup, forward));
    vec3 up = cross(forward, right);

    _horizontal = focus_dist * viewport_width * right;
    _vertical = focus_dist * viewport_height * up;

    _lower_left_corner = _origin - _horizontal * .5 - _vertical * .5 - forward * focus_dist;
    _lens_rad = aperture * .5;
}

ray camera::get_ray(double s, double t) const
{
    vec3 offset = vec3::random_in_unit_disk() * _lens_rad;
    return ray(_origin + offset, _lower_left_corner + s * _horizontal + t * _vertical - _origin - offset);
}
