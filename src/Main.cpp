#include <iostream>

#include "imgproc/image_io.h"
#include "imgproc/pixel_manip.h"
#include "math/ray.h"
#include "math/vec3.hpp"

#include <cstring>
#include <memory>

double is_ray_touching_sphere(const ray& ray, const point3& sphere_center, double sphere_radaius)
{
    vec3 oc = ray.origin() - sphere_center;
    double a = dot(ray.direction(), ray.direction());
    double half_b = dot(ray.direction(), oc);
    double c = dot(oc, oc) - sphere_radaius * sphere_radaius;
    double quarter_discriminant = (half_b * half_b) - (a * c);

    if (quarter_discriminant < 0)
    {
        return -1.0;
    }
    double t = (-half_b - sqrt(quarter_discriminant)) / a;

    return t;
}

color ray_color(const ray& r)
{
    point3 sphere_center(0.5, 0.3, -2.);
    if (double t = is_ray_touching_sphere(r, sphere_center, 0.5); t >= 0.)
    {
        point3 hit_point = r.at(t);
        vec3 N = unit_vector(hit_point - sphere_center);
        std::cout << "N=" << N << "\n";
        return 0.5 * (N + 1.0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    double aspect_ratio = 16.0 / 9.0;
    size_t image_width = 400;
    size_t image_height = image_width / aspect_ratio;
    size_t channels = 3;
    static constexpr char NEW_FILENAME[] = "out.png";

    std::unique_ptr<byte[]> data = alloc_image_buffer(image_width, image_height, channels);

    // Camera
    double viewport_height = 2;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1;

    point3 origin = point3(0., 0., 0.);
    vec3 horizontal = vec3(viewport_width, 0., 0.);
    vec3 vertical = vec3(0., viewport_height, 0.);
    auto lower_left_corner = origin - horizontal / 2. - vertical / 2. - vec3(0., 0., focal_length);

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (ssize_t j = image_height - 1; j >= 0; j--)
    {
        std::cerr << "\rRendering line " << image_height - 1 - j << "   " << std::flush;
        for (ssize_t i = 0; i < image_width; ++i)
        {
            double u = (double)i / (double)(image_width - 1);
            double v = (double)j / (double)(image_height - 1);

            ray current_ray(origin, lower_left_corner + u * horizontal + v * vertical);

            color current_pixel_color = ray_color(current_ray);

            pixel_write(data, i, image_height - 1 - j, image_width, current_pixel_color);
        }
    }

    // Write
    bool res = image_write(NEW_FILENAME, image_width, image_height, channels, data.get());

    return res ? 0 : 1;
}