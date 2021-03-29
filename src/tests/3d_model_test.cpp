#include "../core/vec.h"
#include "../core/load3d.h"

using namespace mypt;

int main() {
    std::string filename = "../../data/model/Armadillo.ply";
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<int3> faces; 
    std::vector<vec2> texcoords;
    loadPly(filename, vertices, normals, faces, texcoords);

    for (auto &v : vertices) Message(v);
    for (auto &f : faces) Message(f);

    return 0;
}