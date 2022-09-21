#include "imgproc/image_io.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <iostream>
#include <mutex>

extern "C" int stbi_write_png_compression_level;

static void init_stb_if_needed()
{
    try
    {
        static std::once_flag of;
        std::call_once(of, []() { stbi_write_png_compression_level = 0; });
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
    }
}

bool image_write(const std::string& path, size_t width, size_t height, size_t channels, byte* data)
{
    init_stb_if_needed();
    size_t stride = width * channels * sizeof(data[0]);
    bool res = (stbi_write_png(path.c_str(), width, height, channels, data, stride) == 1) ? true : false;

    return res;
}

bool image_read(const std::string& path, size_t& width, size_t& height, size_t& channels, byte*& data)
{
    init_stb_if_needed();
    int iwidth, iheight, ichannels;
    data = stbi_load(path.c_str(), &iwidth, &iheight, &ichannels, 0);
    width = static_cast<size_t>(iwidth);
    height = static_cast<size_t>(iheight);
    channels = static_cast<size_t>(ichannels);

    return static_cast<bool>(data);
}

std::unique_ptr<byte[]> alloc_image_buffer(size_t width, size_t height, size_t channels)
{
    size_t total_bytes = width * height * channels * sizeof(byte);
    std::unique_ptr<byte[]> buffer = std::make_unique<byte[]>(total_bytes);

    memset(buffer.get(), 255, total_bytes);

    return buffer;
}
