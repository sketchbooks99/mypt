#pragma once

#include <vector>
#include "../core/Util.h"

// PixelType must be float, vec3, vec4
template <typename PixelType>
class Image {
public:
    Image(int width, int height);

    void set(int x, int y, PixelType val)
    {
        assert(x * y < width * height);
        int base_idx = y * width + x;
        if(nChannels == 1)
            data[base_idx] = val;
        else
        {
            for(int i=0; i<nChannels; i++) {
                data[base_idx+i] = val[i];
            }
        }
    }
    void set(int x, int y, PixelType val) {
        assert(data.size() < x && data[x].size() < y);
        data[x][y] = val;
    }
    PixelType get(int x, int y)
    {
        assert(data.size() < x && data[x].size() < y);
        return data[x][y];
    }

    void write(const std::string& filename, const std::string& format);
private:
    void writePPM();

    unsigned int nChannels;
    unsigned char* data;
    int width, height;
};

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(int width, int height) {
    if(width <= 0 || height <= 0)
        throw std::runtime_error("Image class must have at least 1 pixel!\n");

    size_t pixel_size = sizeof(PixelType) / sizeof(float);
    nChannels = static_cast<unsigned int>(pixel_size);
    data = (char*)malloc(sizeof(char)*width*height*pixel_size);
}

template <typename PixelType>
void Image<PixelType>::writePPM() {
    // PPM file don't support alpha channel, maybe...
    assert(sizeof(PixelType) <= 3);
    
}