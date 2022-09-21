#include "imgproc/pixel_manip.h"
#include "math/common.hpp"

#define IDX2(col, row, width) ((col)*3) + ((row) * (width)*3)

void pixel_write(std::unique_ptr<byte[]>& data, size_t x, size_t y, size_t width, color pixel_color)
{
    size_t currIdx = IDX2(x, y, width);
    data[currIdx + 0] = static_cast<byte>(256 * clamp(pixel_color.x(), 0., 0.99999));
    data[currIdx + 1] = static_cast<byte>(256 * clamp(pixel_color.y(), 0., 0.99999));
    data[currIdx + 2] = static_cast<byte>(256 * clamp(pixel_color.z(), 0., 0.99999));
}