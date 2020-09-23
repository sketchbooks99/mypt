#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <fstream>
#include <vector>
#include "../core/Shape.h"
#include "../core/vec3.h"

struct TriangleMesh {
    TriangleMesh(const std::string &filename, vec3 position, float size, vec3 axis) {
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
        vec3 min = vertices.front(), max = vertices.front();
        for (auto &vertex : vertices) {
            center += vertex / vertices.size();
            for(auto i = 0; i < 3; i++) {
                if(vertex[i] < min[i]) min[i] = vertex[i];
                if(vertex[i] > max[i]) max[i] = vertex[i];
            }
        }

        auto scale = std::numeric_limits<float>::max();
        for (auto i = 0; i < 3; i++) {
            float d = 1e-6f; // Prevent zero division error;
            auto ratio = size / (min[i] - max[i] + d);
            if(ratio < scale) {
                scale = ratio;
            }
        }

        for(auto &vertex : vertices) {
            vertex = (vertex - center) * scale + position;
        }

        // Mesh smoothing
        if(faces.size() > 32) {
            normals = std::vector<vec3>(vertices.size(), vec3());
            auto counts = std::vector<int>(vertices.size(), 0);
            for(auto i = 0; i < faces.size(); i++) {
                for(auto j = 0; j < 3; j++) {
                    auto x = faces[i][j];
                    auto p0 = vertices[faces[i][0]];
                    auto p1 = vertices[faces[i][1]];
                    auto p2 = vertices[faces[i][2]];
                    normals[x] += unit_vector(cross(p2 - p0, p1 - p0));
                    counts[x]++;
                }
            }
            for(auto i=0; i<vertices.size(); i++) {
                normals[i] /= counts[i];
            }
        }
    }

    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<std::vector<int>> faces;
    // std::vector<vec2> uv;
};

class Triangle : public Shape {
    public:
        Triangle() {}
        Triangle(std::shared_ptr<TriangleMesh> &mesh, std::vector<int> face)
            : mesh(mesh), face(face) {
            // Calculate corner vertex of AABB
            vec3 p0 = mesh->vertices[face[0]];
            vec3 p1 = mesh->vertices[face[1]];
            vec3 p2 = mesh->vertices[face[2]];
            min = vec3(); 
            max = vec3();
            for(auto p : {p0, p1, p2}) {
                if (p.x < min.x) min.x = p.x;
                if (p.x > max.x) max.x = p.x;

                if (p.y < min.y) min.y = p.y;
                if (p.y > max.y) max.y = p.y;

                if (p.z < min.z) min.z = p.z;
                if (p.z > max.z) max.z = p.z;
            }
        }
        
        virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        virtual AABB bounding() const;

        vec3 get_normal() const { 
            auto p0 = mesh->vertices[face[0]];
            auto p1 = mesh->vertices[face[1]];
            auto p2 = mesh->vertices[face[2]];
            return unit_vector(cross(p2-p0, p1-p0));
        }

        vec3 get_vertices() const {
            return face[3];
        }

    private:
        std::vector<int> face;
        std::shared_ptr<TriangleMesh> mesh;
        vec3 min, max; // For AABB
};

// ref: https://pheema.hatenablog.jp/entry/ray-tdriangle-intersection
bool Triangle::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    float kEps = 1e-6f;

    auto p0 = mesh->vertices[face[0]];
    auto p1 = mesh->vertices[face[1]];
    auto p2 = mesh->vertices[face[2]];

    vec3 e1 = p1 - p0;
    vec3 e2 = p2 - p0;

    vec3 alpha = cross(r.direction(), e2);
    float det = dot(e1, alpha);

    if(det < fabs(kEps)) return false;

    float invDet = 1.0 / det;
    vec3 ov0 = r.origin() - p0;

    // Check if u satisfies 0 <= u <= 1
    float u = dot(alpha, ov0) * invDet;
    if(u < 0.0f || u > 1.0f) return false;

    vec3 beta = cross(ov0, e1);

    // Check if v satisfies 0 <= v <= 1 & u + v <= 1
    // This can be interpreted to check if v satisfies 0 <= v <= 1-u
    float v = dot(r.direction(), beta) * invDet;
    if(v < 0.0f || u + v > 1.0f) return false;

    // Check if Ray are behind polygon
    float t = dot(e2, beta) * invDet;
    if (t < 0.0f) return false;

    rec.t = t;
    rec.p = r.at(rec.t);

    // ===== Flat shading =====
    // auto normal = unit_vector(cross(e2 - e0, e1 - e0));
    // rec.set_face_normal(r, normal);

    // ===== Smooth shading =====
    auto n0 = mesh->normals[face[0]];
    auto n1 = mesh->normals[face[1]];
    auto n2 = mesh->normals[face[2]];
    auto normal = unit_vector((1 - u - v)*n0 + u*n1 + v*n2);
    rec.set_face_normal(r, normal);

    return true;
}

AABB Triangle::bounding() const {
    return AABB(min, max);
}

std::vector<std::shared_ptr<Shape>> createTriangleMesh(const std::string &filename, vec3 position, 
                                                          float size, vec3 axis) {
    std::vector<std::shared_ptr<Shape>> triangles;
    std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(filename, position, size, axis);
    for(auto &face : mesh->faces) {
        triangles.emplace_back(std::make_shared<Triangle>(mesh, face));
    }

    return triangles;
}

#endif
