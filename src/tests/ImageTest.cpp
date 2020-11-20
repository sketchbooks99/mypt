#include "../core/Image.h"

int main(int argc, const char* argv[]) {
    std::string filename = "../../data/image/image.png";
    Image<RGBA> img(filename);
    img.write("./debug.png", "PNG");
    return 0;
}