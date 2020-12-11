#pragma once

#include "MathUtil.h"

namespace mypt {

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

}