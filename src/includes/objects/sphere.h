#pragma once

#include "objects/hittable.h"

class sphere : public hittable
{
public:
    sphere(point3 center, double rad) : _center(center), _rad(rad) {}
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) override;
    point3 get_center() const
    {
        return _center;
    }
    double radius() const
    {
        return _rad;
    }

private:
    void set_hit_record(const ray& r, double t, hit_record& rec);

private:
    point3 _center;
    double _rad;
};