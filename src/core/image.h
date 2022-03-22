#pragma once

#include "math_util.h"
#include "vec.h"
#include <memory>

namespace mypt {

/** \brief Image object that stores the color informations
 *  This class supports GRAY, RGB, RGBA color representation.
 *  Load/write operations are realized through `stbi` library.
 *  `ImageTexture` also uses this class for texture mapping */
template <typename PixelType>
class Image {
public:
    explicit Image() = default;
    explicit Image(int width, int height);
    explicit Image(const std::string& filename);
    ~Image() { if(data) data.reset(); }
    void set(int x, int y, const PixelType& val)
    {
        assert(x < width && y < height);
        int idx = y * width + x;
        data[idx] = val;
    }
    const PixelType& get(int x, int y) const 
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

    const PixelType* getData() { return data.get(); }
protected:
    int nChannels;
    std::unique_ptr<PixelType[]> data;
    int width, height;
};

}