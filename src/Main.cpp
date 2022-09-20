#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define IDX2(col, row, width) ((col)*3) + ((row) * (width)*3)

#include "math/vec3.hpp"

bool write_image(const std::string& path, size_t width, size_t height, size_t channels, u_char* data)
{
    size_t stride = width * channels * sizeof(data[0]);
    bool res = (stbi_write_png(path.c_str(), width, height, channels, data, stride) == 1) ? true : false;

    return res;
}
extern "C" int stbi_write_png_compression_level;

int main()
{
    vec3 vv;
    stbi_write_png_compression_level = 0;
    std::cout << "Hello\n";
    int width, height, channels;
    static constexpr char FILENAME[] = "file_example_PNG_3MB.png";
    static constexpr char NEW_FILENAME[] = "out.png";
    unsigned char* data = stbi_load(FILENAME, &width, &height, &channels, 0);
    int stride = width * channels * sizeof(data[0]);

    int col = width / 2;
    int row = height / 4;
    for (int col = width / 2; col < width; ++col)
    {
        for (int row = height / 4; row < height / 2; ++row)
        {
            data[IDX2(col, row, width) + 0] = 255;
            data[IDX2(col, row, width) + 1] = 0;
            data[IDX2(col, row, width) + 2] = 0;
        }
    }

    //  int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
    bool res = write_image(NEW_FILENAME, width, height, channels, data);
    return res;
    // int res = stbi_write_jpg(NEW_FILENAME, width, height, channels, data, 100);
}