#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "../core/Util.h"

// Should RGB value be implemented by std::vector? 
// Each pixel have channel size vector? I have no good idea to implement. 
template <typename T>
struct Pixel {
    T* data;
};

class Image {
public:
    enum class PixelType{ RGB, RGBA, GRAY };
    Image(int width, int height, PixelType type = PixelType::RGB);
private:
    void allocate(int width, int height, PixelType type);

    int width, height;
};

Image::Image(int width, int height, PixelType type) {

}

void Image::allocate(int width, int height, PixelType type) {
    
}

#endif