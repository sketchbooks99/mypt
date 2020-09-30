#ifndef IMAGE_H
#define IMAGE_H

#include "../stb_image_write.h"

struct Pixel {

};

class Image {
public:
    enum class PixelType{ RGB, RGBA, GRAY };
    Image(int width, int height, PixelType type = PixelType::RGB);
private:
    void allocate(int width, int height, PixelType type);

    int width, height;
};

#endif