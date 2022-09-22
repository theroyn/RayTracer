#pragma once

#include "vec3.hpp"

class ray
{
public:
    ray() {}
    ray(point3 origin, vec3 direction) : o(origin), d(direction) {}
    point3 origin() const
    {
        return o;
    }
    vec3 direction() const
    {
        return d;
    }
    vec3 at(double t) const
    {
        return o + t * d;
    }

private:
    point3 o;
    vec3 d;
};