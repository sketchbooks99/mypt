#pragma once

#include "MathUtil.h"

namespace mypt {

// PixelType must be GRAY, RGB, RGBA
template <typename PixelType>
class Image {
public:
    Image(); 
    Image(int width, int height);
    Image(const std::string& filename);
    ~Image() { if (data != nullptr) delete[] data; }
    void set(int x, int y, PixelType val)
    {
        assert(x < width && y < height);
        int idx = y * width + x;
        data[idx] = val;
    }
    PixelType get(int x, int y) const 
    {
        assert(x < width && y < height);
        int idx = y * width + x;
        return data[idx];
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void build(int width, int height);

    void load(const std::string& filename);
    void write(const std::string& filename, const std::string& format);

    PixelType* getData() { return data; }
protected:
    int nChannels;
    PixelType* data;
    int width, height;
};

}