#include "objects/hittable_list.h"

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    bool hit_anything = false;
    hit_record temp_rec;
    double closest_so_far = t_max;
    for (std::shared_ptr<hittable> h : _hittables)
    {
        if (h->hit(r, t_min, closest_so_far, temp_rec))
        {
            rec = temp_rec;
            hit_anything = true;
            closest_so_far = temp_rec.t;
        }
    }

    return hit_anything;
}

void hittable_list::add(std::shared_ptr<hittable> h)
{
    _hittables.push_back(h);
}

void hittable_list::clear()
{
    _hittables.clear();
}