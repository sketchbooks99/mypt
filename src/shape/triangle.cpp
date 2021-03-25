#include "triangle.h"

namespace mypt {

// ---------------------------------------------------------------------------
TriangleMesh::TriangleMesh(const std::string &filename, float size, vec3 axis, bool isSmooth) {
    if(filename.substr(filename.length() - 4) == ".obj")
    {
        std::ifstream ifs(filename, std::ios::in);
        Assert(ifs.is_open(), "The obj file '"+filename+"' is not existed!\n");
        while (!ifs.eof())
        {
            std::string line;
            if (!std::getline(ifs, line))
                break;

            // creae string stream
            std::istringstream iss(line);
            std::string header;
            iss >> header;

            // vertex --------------------------------------
            if (header == "v")
            {
                float x, y, z;
                iss >> x >> y >> z;
                x *= axis.x;
                y *= axis.y;
                z *= axis.z;
                vertices.emplace_back(x, y, z);
            }
            else if (header == "f")
            {
                // temporal vector to store face information
                std::vector<int> temp_vert_faces;
                std::vector<int> temp_norm_faces;

                // Future work -----------------------------------
                /*std::vector<int> temp_tex_faces;
                std::vector<int> temp_norm_faces;*/
                // ------------------------------------------------ 
                for (std::string buffer; iss >> buffer;)
                {
                    int vert_idx, tex_idx, norm_idx;
                    if (sscanf(buffer.c_str(), "%d/%d/%d", &vert_idx, &tex_idx, &norm_idx) == 3)
                    {
                        // Input - index(vertex)/index(texture)/index(normal)
                        temp_vert_faces.emplace_back(vert_idx - 1);
                        // temp_tex_faces.emplace_back(tex_idx - 1);
                        temp_norm_faces.emplace_back(norm_idx - 1);
                    }
                    else if (sscanf(buffer.c_str(), "%d//%d", &vert_idx, &norm_idx) == 2)
                    {
                        // Input - index(vertex)//index(normal)
                        temp_vert_faces.emplace_back(vert_idx - 1);
                        temp_norm_faces.emplace_back(norm_idx - 1);
                    }
                    else if (sscanf(buffer.c_str(), "%d/%d", &vert_idx, &tex_idx) == 2)
                    {
                        // Input - index(vertex)/index(texture)
                        temp_vert_faces.emplace_back(vert_idx - 1);
                        //temp_tex_faces.emplace_back(tex_idx - 1);
                    }
                    else if (sscanf(buffer.c_str(), "%d", &vert_idx) == 1)
                    {
                        // Input - index(vertex)
                        temp_vert_faces.emplace_back(vert_idx - 1);
                    }
                    else
                        Throw("Invalid format in face information input.\n");
                }

                Assert(temp_vert_faces.size() >= 3, "The number of faces is less than 3.\n");

                if (temp_vert_faces.size() == 3) {
                    int3 face;
                    face[0] = temp_vert_faces[0];
                    face[1] = temp_vert_faces[1];
                    face[2] = temp_vert_faces[2];
                    faces.emplace_back(face);
                }

                /** NOTE: Get more then 4 inputs.
                 * This case is implemented under the assumption that mesh are configurd 
                 * by quad and inputs are partitioned with 4 stride when face input are 
                 * more than 4. */
                else
                {
                    for (int i = 0; i<int(temp_vert_faces.size() / 4); i++)
                    {
                        // The index value of 0th vertex in quad
                        auto base_idx = i * 4;
                        int3 face1;
                        face1[0] = temp_vert_faces[base_idx + 0];
                        face1[1] = temp_vert_faces[base_idx + 1];
                        face1[2] = temp_vert_faces[base_idx + 2];
                        faces.emplace_back(face1);
                        int3 face2;
                        face2[0] = temp_vert_faces[base_idx + 2];
                        face2[1] = temp_vert_faces[base_idx + 3];
                        face2[2] = temp_vert_faces[base_idx + 0];
                        faces.emplace_back(face2);
                    }
                }
            }
        }
        ifs.close();
    }

    for (auto& vertex : vertices) {
        vertex = vertex * size;
    }

    // Mesh smoothing
    /** NOTE:
     * When surface smoothing is enabled, all vertices have only one normal.
     * When smoothing is disabled, normals of each vertices are calculated in
     * each triangle edges, and there is no need to store normals in vector. */
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
std::vector<std::shared_ptr<Shape>> createTriangleMesh(const std::string &filename,
                                                          float size, vec3 axis, bool isSmooth) {
    std::vector<std::shared_ptr<Shape>> triangles;
    std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(filename, size, axis, isSmooth);
    for(auto &face : mesh->faces) {
        triangles.emplace_back(std::make_shared<Triangle>(mesh, face));
    }

    return triangles;
}

}