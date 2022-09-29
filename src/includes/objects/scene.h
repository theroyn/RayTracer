#pragma once

#include "objects/hittable_list.h"

hittable_list random_scene();

// smaller scene with dielectric material mainly for debugging purposes.
hittable_list dielectric_scene();