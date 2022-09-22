#pragma once

#include "math/ray.h"
#include "objects/hittable.h"

class material
{
public:
    virtual bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
    lambertian(const color& albedo) : _albedo(albedo) {}
    virtual bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    color _albedo;
};

class metal : public material
{
public:
    metal(const color& albedo) : _albedo(albedo) {}
    virtual bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    color _albedo;
};
