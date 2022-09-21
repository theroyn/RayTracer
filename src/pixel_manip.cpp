#include "imgproc/pixel_manip.h"

#define IDX2(col, row, width) ((col)*3) + ((row) * (width)*3)

void pixel_write(std::unique_ptr<byte[]>& data, size_t x, size_t y, size_t width, color pixel_color)
{
    size_t currIdx = IDX2(x, y, width);
    data[currIdx + 0] = 255.999 * pixel_color.x();
    data[currIdx + 1] = 255.999 * pixel_color.y();
    data[currIdx + 2] = 255.999 * pixel_color.z();
}