#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include "../core/Shape.h"

namespace mypt {

struct TriangleMesh {
    TriangleMesh(const std::string &filename, float size, vec3 axis, bool isSmooth);
    /* TriangleMesh(const std::vector<vec3> vertices, 
                 const std::vector<vec3>& normals, 
                 const std::vector<std::vector<int>> faces) {} */

    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<int3> faces;
    // std::vector<vec2> uv;
};

class Triangle final : public Shape {
public:
    Triangle() {}
    Triangle(std::shared_ptr<TriangleMesh> &mesh, int3 face)
        : mesh(mesh), face(face) {
        // Calculate corner vertex of AABB
        vec3 p0 = mesh->vertices[face[0]];
        vec3 p1 = mesh->vertices[face[1]];
        vec3 p2 = mesh->vertices[face[2]];
        min = vec3(); 
        max = vec3();
        for(auto p : {p0, p1, p2}) {
            for(int i=0; i<3; i++) {
                if(min[i] > p[i]) min[i] = p[i];
                if(max[i] < p[i]) max[i] = p[i];
            }
        }
    }
    
    bool intersect(const Ray& r, Float t_min, Float t_max, HitRecord& rec) const override;
    AABB bounding() const override { return AABB(min, max); }

    vec3 get_normal() const {
        auto p0 = mesh->vertices[face[0]];
        auto p1 = mesh->vertices[face[1]];
        auto p2 = mesh->vertices[face[2]];
        return normalize(cross(p2-p0, p1-p0));
    }

    std::vector<vec3> get_vertices() const {
        return { mesh->vertices[face[0]], mesh->vertices[face[1]], mesh->vertices[face[2]] };
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Triangle : {" << std::endl;
        oss << "\tp0 : " << mesh->vertices[face[0]] << ", ";
        oss << "p1 : " << mesh->vertices[face[1]] << ", ";
        oss << "p2 : " << mesh->vertices[face[2]] << std::endl;
        oss << "}";
        return oss.str();
    }

private:
    std::shared_ptr<TriangleMesh> mesh;
    int3 face;
    vec3 min, max; // For AABB
};

std::vector<std::shared_ptr<Shape>> createTriangleMesh(const std::string & filename, float size, vec3 axis, 
                                                        bool isSmooth=true);

}                                                    
