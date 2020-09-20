#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <fstream>
#include "Triangle.h"
#include "../core/vec3.h"
// #include "../core/BVH.h"

class TriangleMesh : public Shape {
public:
    TriangleMesh() {}
    TriangleMesh(const std::string &filename, vec3 position, float size, vec3 axis, std::shared_ptr<Material> m)
        : mat_ptr(m) 
    {
        if(filename.substr(filename.length() - 4) == ".obj") {
            std::ifstream ifs(filename, std::ios::in);
            for(std::string buffer; ifs >> buffer; ) {
                if(buffer == "v") {
                    float x, y, z;
                    ifs >> x >> y >> z;
                    x *= axis.x;
                    y *= axis.y;
                    z *= axis.z;
                    vertices.emplace_back(x, y, z);
                    std::cerr << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
                } else if(buffer == "f") {
                    faces.emplace_back(std::vector<int>(3, 0));
                    for(auto i=0; i<3; i++) {
                        ifs >> faces.back()[i];
                        faces.back()[i]--;
                    }
                }
            }
            ifs.close();
        }

        // Transformation
        vec3 center;
        auto min = vertices.front(), max = vertices.front();
        for (auto &vertex : vertices) {
            center += vertex / vertices.size();
            for(auto i = 0; i < 3; i++) {
                if(vertex[i] < min[i]) min[i] = vertex[i];
                if(vertex[i] > max[i]) max[i] = vertex[i];
            }
        }
        // Prevent over the maximum value of float
        auto scale = std::numeric_limits<float>::max();
        for(auto i=0; i<3; i++) {
            float d = 1e-6f; // Prevent zero division
            auto ratio = size / (min[i] - max[i]);
            if(ratio < scale) {
                scale = ratio;
            }
        }

        for(auto &vertex : vertices) {
            vertex = (vertex - center) * scale + position;
            // std::cerr << "vertex: " << vertex << std::endl;
            // std::cerr << "center: " << center << std::endl;
        }
        for(auto &face : faces) {
            triangles.emplace_back(new Triangle(vertices[face[0]], vertices[face[1]], vertices[face[2]], mat_ptr));
        }
        
        min = (min - center) * scale + position;
        max = (max - center) * scale + position;

        // Mesh smoothing
        if(faces.size() > 32) {
            normals = std::vector<vec3>(vertices.size(), vec3());
            auto counts = std::vector<int>(vertices.size(), 0);
            for(auto i = 0; i < faces.size(); i++) {
                for(auto j = 0; j < 3; j++){
                    auto x = faces[i][j];
                    normals[x] += triangles[i]->get_normal();
                    counts[x]++;
                }
            }
            for(auto i=0; i<vertices.size(); i++) {
                normals[i] /= counts[i];
            }
        }
    }
    
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
    virtual bool bounding(double t0, double t1, AABB& output_box) const;

private: 
    std::vector<vec3> vertices, normals;
    std::vector<std::vector<int>> faces;
    std::vector<std::shared_ptr<Triangle>> triangles;
    std::shared_ptr<Material> mat_ptr;
    vec3 min, max;
};

bool TriangleMesh::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    for(auto triangle : triangles) {
        auto intersectted = triangle->intersect(r, t_min, t_max, rec);
        if(intersectted) return true;
    }
    return false;
}

bool TriangleMesh::bounding(double t0, double t1, AABB& output_box) const {
    output_box = AABB(min, max);
    return true;
}

#endif
