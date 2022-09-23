#include "imgproc/image_io.h"
#include "imgproc/pixel_manip.h"
#include "math/common.hpp"
#include "math/ray.h"
#include "math/vec3.hpp"
#include "objects/camera.h"
#include "objects/hittable_list.h"
#include "objects/material.h"
#include "objects/scene.h"
#include "objects/sphere.h"

#include <algorithm>
#include <cstring>
#include <execution>
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
    hittable_list world = random_scene();

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render
    size_t cnt = 0;
    std::vector is(image_width, 0);
    std::vector js(image_height, 0);
    for (int idx = 0; idx < is.size(); ++idx)
    {
        is[idx] = idx;
    }
    for (int idx = 0; idx < js.size(); ++idx)
    {
        js[idx] = idx;
    }

    std::cout << image_width << " " << image_height << "\n";

    std::for_each(std::execution::par_unseq, js.rbegin(), js.rend(),
                  [&](int& j)
                  {
                      std::for_each(std::execution::par_unseq, is.begin(), is.end(),
                                    [&](int& i)
                                    {
                                        color current_pixel_color;
                                        for (size_t s = 0; s < samples_per_pixel; ++s)
                                        {
                                            double u = ((double)i + random_double()) / (double)(image_width - 1);
                                            double v = ((double)j + random_double()) / (double)(image_height - 1);
                                            ray current_ray = cam.get_ray(u, v);
                                            color sample_color = ray_color(current_ray, world, max_depth);
                                            // leaving here for debugging darkness
                                            // if (sample_color.length_squared() < 0.4 && j >= image_height / 2.)
                                            // {
                                            //     color nnnnn = ray_color(current_ray, world, max_depth);
                                            //     // std::cout << i << "," << image_height - 1 - j << ": " << sample_color << "\n";
                                            //     sample_color = vec3(1., 0., 0.);
                                            // }
                                            current_pixel_color += sample_color;
                                        }
                                        current_pixel_color /= samples_per_pixel;

                                        // this code has a race condition, but I don't care, the progress printed is reliable enough.
                                        if (i == image_width - 1)
                                        {
                                            cnt++;
                                            std::cerr << "\rRendered line " << cnt << "/" << image_height << "   (" << image_height - 1 - j
                                                      << ")"
                                                      << "   " << std::flush;
                                        }

                                        // modify each pixel separately without changing the container, so it's thread-safe
                                        pixel_write(data, i, image_height - 1 - j, image_width, current_pixel_color);
                                    });
                  });

    std::cerr << "\ndone\n";

    // Write
    bool res = image_write(NEW_FILENAME, image_width, image_height, channels, data.get());

    return res ? 0 : 1;
}