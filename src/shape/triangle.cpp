#include "triangle.h"
#include "../core/load3d.h"

namespace mypt {

// ---------------------------------------------------------------------------
TriangleMesh::TriangleMesh(const std::string &filename, bool isSmooth) {
    if (filename.substr(filename.length() - 4) == ".obj") {
        Message("Loading OBJ file '", filename, "' ...");
        loadObj(filename, vertices, normals, faces, texcoords);
    }
    else if (filename.substr(filename.length() - 4) == ".ply") {
        Message("Loading PLY file '", filename, "' ...");
        loadPly(filename, vertices, normals, faces, texcoords);
    }
    
    if(isSmooth) {
        normals.resize(vertices.size());
        auto counts = std::vector<int>(vertices.size(), 0);
        for(auto &face : faces)
        {
            auto p0 = vertices[face[0]];
            auto p1 = vertices[face[1]];
            auto p2 = vertices[face[2]];
            auto N = normalize(cross(p2-p0, p1-p0));

            // Normal smoothing
            auto idx = face[0];
            normals[idx] += N;
            counts[idx]++;
            idx = face[1];
            normals[idx] += N;
            counts[idx]++;
            idx = face[2];
            normals[idx] += N;
            counts[idx]++;
        }
        for (auto i = 0; i < (int)vertices.size(); i++)
        {
            normals[i] /= counts[i];
            normals[i] = normalize(normals[i]);
        }
    }
}

// ---------------------------------------------------------------------------
// ref: https://pheema.hatenablog.jp/entry/ray-tdriangle-intersection
bool Triangle::intersect(const Ray& r, Float t_min , Float t_max, SurfaceInteraction& si) const {
    auto p0 = mesh->vertices[face[0]];
    auto p1 = mesh->vertices[face[1]];
    auto p2 = mesh->vertices[face[2]];

    vec3 e1 = p1 - p0;
    vec3 e2 = p2 - p0;

    vec3 alpha = cross(r.direction(), e2);
    float det = dot(e1, alpha);

    if(fabs(det) < eps) return false;

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
    if (t < t_min || t > t_max) return false;

    si.t = t;
    si.p = r.at(si.t);

    vec3 normal;
    // ===== Flat shading =====
    if(mesh->normals.empty()) {
        normal = normalize(cross(e2, e1));
    }
    // ===== Smooth shading =====
    else {
        auto n0 = mesh->normals[face[0]];
        auto n1 = mesh->normals[face[1]];
        auto n2 = mesh->normals[face[2]];
        normal = normalize((1.0f - u - v)*n0 + u*n1 + v*n2);
    }
    si.set_face_normal(r, normal);
    return true;
}

// ---------------------------------------------------------------------------
std::vector<std::shared_ptr<Shape>> createTriangleMesh(const std::string &filename, bool isSmooth) {
    std::vector<std::shared_ptr<Shape>> triangles;
    std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(filename, isSmooth);
    for(auto &face : mesh->faces) {
        triangles.emplace_back(std::make_shared<Triangle>(mesh, face));
    }

    return triangles;
}

}