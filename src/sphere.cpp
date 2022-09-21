#include "objects/sphere.h"

void sphere::set_hit_record(const ray& r, double t, hit_record& rec) const
{
    rec.t = t;
    rec.p = r.at(t);

    vec3 outward_normal = (rec.p - _center) / _rad; // asumption that the point is on the sphere
    rec.set_face_normal(r, outward_normal);
}

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    bool is_hit = false;
    vec3 oc = r.origin() - _center;
    double a = dot(r.direction(), r.direction());
    double half_b = dot(r.direction(), oc);
    double c = dot(oc, oc) - _rad * _rad;
    double quarter_discriminant = (half_b * half_b) - (a * c);

    if (quarter_discriminant >= 0)
    {
        double nearest_root = (-half_b - sqrt(quarter_discriminant)) / a;
        if (nearest_root >= t_min && nearest_root <= t_max)
        {
            is_hit = true;
        }
        else
        {
            nearest_root = (-half_b + sqrt(quarter_discriminant)) / a;
            if (nearest_root >= t_min && nearest_root <= t_max)
            {
                is_hit = true;
            }
        }

        if (is_hit)
        {
            set_hit_record(r, nearest_root, rec);
        }
    }

    return is_hit;
}