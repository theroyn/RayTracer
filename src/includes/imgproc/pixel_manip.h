#pragma once

#include <cstddef>
#include <memory>

#include "math/color.h"
#include "core/types.h"

void pixel_write(std::unique_ptr<byte[]>& data, size_t x, size_t y, size_t width, color pixel_color);
