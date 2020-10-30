#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "../core/Util.h"

// // Should RGB value be implemented by std::vector? 
// // Each pixel have channel size vector? I have no good idea to implement. 
// template <typename T>
// struct Pixel {
//     const T get() { return val; }
//     const void set(T val) {
//         this->val = val; 
//     }
// private:
//     T val; // pixel value 
// };

// PixelType should be float(int) or float(int)3 or float(int)4
template <typename PixelType>
class Image {
public:
    // enum class PixelType{ RGB, RGBA, GRAY };
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

template <typename PixelType>
Image<PixelType>::Image(int width, int height) {
    if(width <= 0 || height <= 0)
        throw std::runtime_error("Image class must have at least 1 pixel!\n");
        
    data.resize(width);
    for(auto &d : data)
    {
        d.resize(height);
    }
}

#endif