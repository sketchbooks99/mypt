#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "../core/Util.h"

template <typename PixelType>
class Image {
public:
    Image(int width, int height);

    void set(int x, int y, PixelType val) {
        assert(data.size() < x && data[x].size() < y);
        data[x][y] = val;
    }
    Pixeltype get(int x, int y)
    {
        assert(data.size() < x && data[x].size() < y);
        return data[x][y];
    }
private:
    std::vector<std::vector<PixelType>> data;
    int width, height;
};

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(int width, int height) {
    if(width <= 0 || height <= 0)
        throw std::runtime_error("Image class must have at least 1 pixel!\n");

    // Construct 2 dimensional vector with width and height
    data.resize(width);
    for(auto &d : data)
    {
        d.resize(height);
    }
}

#endif