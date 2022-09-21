#pragma once
#include <cstddef>
#include <memory>
#include <string>

#include "math/color.h"
#include "core/types.h"

bool image_write(const std::string& path, size_t width, size_t height, size_t channels, byte* data);
bool image_read(const std::string& path, size_t& width, size_t& height, size_t& channels, byte*& data);

std::unique_ptr<byte[]> alloc_image_buffer(size_t width, size_t height, size_t channels);
