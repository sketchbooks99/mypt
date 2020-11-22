#pragma once

#include <vector>
#include "MathUtil.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb_image_write.h"

// PixelType must be GRAY, RGB, RGBA
template <typename PixelType>
class Image {
public:
    Image(int width, int height);
    Image(const std::string& filename);
    ~Image() { delete[] data; }
    void set(int x, int y, PixelType val)
    {
        assert(x < width && y < height);
        int idx = y * width + x;
        data[idx] = val;
    }
    PixelType get(int x, int y) const 
    {
        assert(x < width && y < height);
        return data[y * width + x];
    }
    void load(const std::string& filename);
    void write(const std::string& filename, const std::string& format);
protected:
    int nChannels;
    PixelType* data;
    int width, height;
};

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(int width, int height)
: width(width), height(height){
    // ASSERT(width > 0 && height > 0, "Image class must have at least 1 pixel\n");

    nChannels = static_cast<int>(sizeof(PixelType));
    data = (PixelType*)malloc(sizeof(PixelType)*width*height);
}

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(const std::string& filename)
{
    nChannels = static_cast<int>(sizeof(PixelType));
    data = reinterpret_cast<PixelType*>(stbi_load(filename.c_str(), &width, &height, &nChannels, nChannels));
    if(!data)
        throw std::runtime_error("Image file '"+filename+"'can't be loaded! Please check file path or format!\n");
}

// --------------------------------------------------------------------------------
template <typename PixelType>
void Image<PixelType>::load(const std::string& filename)
{   
    nChannels = static_cast<int>(sizeof(PixelType));
    data = reinterpret_cast<PixelType*>(stbi_load(filename.c_str(), &width, &height, &nChannels, nChannels));
    if(!data)
        throw std::runtime_error("Image file can't be loaded! Please check file path or format!\n");
}

// --------------------------------------------------------------------------------
template <typename PixelType>
void Image<PixelType>::write(const std::string& filename, const std::string& format)
{
    if(format == "png" || format == "PNG")
    {
        // stbi_flip_vertically_on_write(true);
        stbi_write_png(filename.c_str(), width, height, nChannels, data, 4 - nChannels);
    }
    if(format == "jpg" || format == "JPG")
    {
        ASSERT(nChannels <= 3, "JPG doesn't support alpha channel!\n");
    }
}