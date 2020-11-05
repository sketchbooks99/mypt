#pragma once

#include <vector>
#include "MathUtil.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb_image_write.h"

// PixelType must be float, vec3, vec4
template <typename PixelType>
class Image {
public:
    Image(int width, int height);

    void set(int x, int y, PixelType val)
    {
        assert(x < width && y < height);
        int idx = y * width + x;
        data[idx] = val;
    }
    // PixelType get(int x, int y)
    // {
    //     assert(x < width && y < height);
    //     return data[x][y];
    // }

    void write(const std::string& filename, const std::string& format);
private:
    unsigned int nChannels;
    PixelType* data;
    int width, height;
};

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(int width, int height)
: width(width), height(height){
    if(width <= 0 || height <= 0)
        throw std::runtime_error("Image class must have at least 1 pixel!\n");

    size_t pixel_size = sizeof(PixelType) / sizeof(unsigned char);
    nChannels = static_cast<unsigned int>(pixel_size);
    data = (PixelType*)malloc(sizeof(PixelType)*width*height);
}

// --------------------------------------------------------------------------------
template <typename PixelType>
void Image<PixelType>::write(const std::string& filename, const std::string& format)
{
    if(format == "png" || format == "PNG")
    {
        stbi_write_png(filename.c_str(), width, height, nChannels, data, 0);
    }
    if(format == "jpg" || format == "JPG")
    {
        ASSERT(nChannels <= 3, "JPG doesn't support alpha channel!\n");
    }
}

// template <typename PixelType>
// void Image<PixelType>::writePPM() {
//     // PPM file don't support alpha channel, maybe...
//     assert(sizeof(PixelType) <= 3);

//     for(int y=0; y<height; y++) 
//     {
//         for(int x=0; x<width; x++)
//         {

//         }
//     }
// }