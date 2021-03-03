#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb_image_write.h"

namespace mypt {

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(int width, int height)
: width(width), height(height){
    Assert(width > 0 && height > 0, "Image class must have at least 1 pixel\n");
    nChannels = static_cast<int>(sizeof(PixelType));
    data = new PixelType[width*height];
}
template Image<GRAY>::Image(int, int);
template Image<RGB>::Image(int, int);
template Image<RGBA>::Image(int, int);

// --------------------------------------------------------------------------------
template <typename PixelType>
Image<PixelType>::Image(const std::string& filename)
{
    nChannels = static_cast<int>(sizeof(PixelType));
    data = reinterpret_cast<PixelType*>(stbi_load(filename.c_str(), &width, &height, &nChannels, nChannels));
    Assert(data, "Image file '"+filename+"' can't be loaded! Please check file path or format!\n");
}
template Image<GRAY>::Image(const std::string&);
template Image<RGB>::Image(const std::string&);
template Image<RGBA>::Image(const std::string&);

// --------------------------------------------------------------------------------
template <typename PixelType>
void Image<PixelType>::allocate(int width, int height) {
    this->width = width; 
    this->height = height;
    nChannels = static_cast<int>(sizeof(PixelType));
    data = new PixelType[width*height];
}
template void Image<GRAY>::allocate(int, int);
template void Image<RGB>::allocate(int, int);
template void Image<RGBA>::allocate(int, int);

// --------------------------------------------------------------------------------
template <typename PixelType>
void Image<PixelType>::load(const std::string& filename)
{   
    nChannels = static_cast<int>(sizeof(PixelType));
    data = reinterpret_cast<PixelType*>(stbi_load(filename.c_str(), &width, &height, &nChannels, 0));
    Assert(data, "Image file '"+filename+"' can't be loaded! Please check file path or format!\n");
}
template void Image<GRAY>::load(const std::string&);
template void Image<RGB>::load(const std::string&);
template void Image<RGBA>::load(const std::string&);

// --------------------------------------------------------------------------------
template <typename PixelType>
void Image<PixelType>::write(const std::string& filename, const std::string& format)
{
    if(format == "png" || format == "PNG")
    {
        // stbi_flip_vertically_on_write(true);
        stbi_write_png(filename.c_str(), width, height, nChannels, data, 4 - nChannels);
    }
    if(format == "jpg" || format == "JPG")
    {
        stbi_write_jpg(filename.c_str(), width, height, 3, data, 100);
    }
}
template void Image<GRAY>::write(const std::string&, const std::string&);
template void Image<RGB>::write(const std::string&, const std::string&);
template void Image<RGBA>::write(const std::string&, const std::string&);

}