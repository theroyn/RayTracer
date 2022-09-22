#pragma once

#include "objects/hittable.h"

#include <memory>

class material;

class sphere : public hittable
{
public:
    sphere(point3 center, double rad, std::shared_ptr<material> mat) : _center(center), _rad(rad), _mat(mat) {}
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    point3 get_center() const
    {
        return _center;
    }
    double radius() const
    {
        return _rad;
    }

private:
    void set_hit_record(const ray& r, double t, hit_record& rec, std::shared_ptr<material> mat) const;

private:
    point3 _center;
    double _rad;
    std::shared_ptr<material> _mat;
};