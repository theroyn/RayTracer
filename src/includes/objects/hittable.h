#pragma once

#include "math/ray.h"

class hittable
{
    virtual bool hit(const ray& r);
};