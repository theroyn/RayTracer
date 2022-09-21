#pragma once

#include "objects/hittable.h"

#include <memory>
#include <vector>

class hittable_list
{
public:
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    void add(std::shared_ptr<hittable>);
    void clear();

private:
    std::vector<std::shared_ptr<hittable>> _hittables;
};
