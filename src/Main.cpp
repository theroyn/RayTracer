#include "imgproc/image_io.h"
#include "imgproc/pixel_manip.h"
#include "math/common.hpp"
#include "math/ray.h"
#include "math/vec3.hpp"
#include "objects/camera.h"
#include "objects/hittable_list.h"
#include "objects/material.h"
#include "objects/sphere.h"

#include <cstring>
#include <iostream>
#include <memory>

color ray_color(const ray& r, const hittable_list& world, size_t depth)
{
    if (depth <= 0)
    {
        return color(0., 0., 0.);
    }

    hit_record rec;

    if (world.hit(r, 0.0001, infinity, rec))
    {
        color attenuation;
        ray scattered_ray;
        color col = color(0., 0., 0);
        if (rec.mat->scatter(r, rec, attenuation, scattered_ray))
        {
            col = attenuation * ray_color(scattered_ray, world, depth - 1);
        }
        // else return 0

        return col;
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    static constexpr double aspect_ratio = 16.0 / 9.0;
    static constexpr size_t image_width = 600;
    static constexpr size_t image_height = image_width / aspect_ratio;
    static constexpr size_t channels = 3;
    static constexpr int samples_per_pixel = 100;
    static constexpr size_t max_depth = 50;
    static constexpr char NEW_FILENAME[] = "out.png";

    std::unique_ptr<byte[]> data = alloc_image_buffer(image_width, image_height, channels);

    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0., 0., -1.4), 0.5, std::make_shared<metal>(vec3(0.8), 0.)));
    world.add(std::make_shared<sphere>(point3(-0.7, 0.2, -1.5), 0.2, std::make_shared<metal>(vec3(0.5), 0.9)));
    world.add(std::make_shared<sphere>(point3(-0.3, 0., -0.4), 0.1, std::make_shared<metal>(vec3(0.6, 0.8, 0.2), 0.4)));
    world.add(std::make_shared<sphere>(point3(1.0, 0.5, -1.2), 0.2, std::make_shared<lambertian>(vec3(0.5, 0.3, 0.9))));
    world.add(std::make_shared<sphere>(point3(0., -100.5, -1.), 100, std::make_shared<lambertian>(vec3(0.3, 0.2, 0.1))));

    // Camera
    camera cam(aspect_ratio);

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (ssize_t j = image_height - 1; j >= 0; j--)
    {
        std::cerr << "\rRendering line " << image_height - 1 - j << "   " << std::flush;
        for (ssize_t i = 0; i < image_width; ++i)
        {
            color current_pixel_color;
            for (size_t s = 0; s < samples_per_pixel; ++s)
            {
                double u = ((double)i + random_double()) / (double)(image_width - 1);
                double v = ((double)j + random_double()) / (double)(image_height - 1);
                ray current_ray = cam.get_ray(u, v);
                current_pixel_color += ray_color(current_ray, world, max_depth);
            }
            current_pixel_color /= samples_per_pixel;

            pixel_write(data, i, image_height - 1 - j, image_width, current_pixel_color);
        }
    }

    std::cerr << "\ndone\n";

    // Write
    bool res = image_write(NEW_FILENAME, image_width, image_height, channels, data.get());

    return res ? 0 : 1;
}