#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "../core/Util.h"

// Should RGB value be implemented by std::vector? 
// Each pixel have channel size vector? I have no good idea to implement. 
struct Pixel {
    int operator[](int i) const {
        try {
            return values[i];
        } 
        catch (std::out_of_range &oor) {
            std::cout << "Index out of range." << std::endl;
        }
    }
    std::vector<int> values;
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