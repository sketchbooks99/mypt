#pragma once

#include "math_util.h"
#include "vec.h"

namespace mypt {

/** \brief Image object that stores the color informations
 *  This class supports GRAY, RGB, RGBA color representation.
 *  Load/write operations are realized through `stbi` library.
 *  `ImageTexture` also uses this class for texture mapping */
template <typename PixelType>
class Image {
public:
    explicit Image() {}
    explicit Image(int width, int height);
    explicit Image(const std::string& filename);
    ~Image() { if(data) delete[] data; }
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

    // Allocate image with specified size.
    void allocate(int width, int height);

    void load(const std::string& filename);
    void write(const std::string& filename, const std::string& format);

    PixelType* getData() { return data; }
protected:
    int nChannels;
    PixelType* data;
    int width, height;
};

}