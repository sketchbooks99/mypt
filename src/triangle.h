#ifndef Triangle_h
#define Triangle_h

#include "Hittable.h"
#include "vec3.h"

class Triangle : public Hittable {
    public:
        Triangle() {}
        Triangle(vec3 p0, vec3 p1, vec3 p2, shared_ptr<Material> m)
            : v{p0, p1, p2}, mat_ptr(m) {
            // Calculate corner vertex of AABB
            for(auto p : {p0, p1, p2}) {
                if (p.x < min.x) min.x = p.x;
                if (p.x > max.x) max.x = p.x;

                if (p.y < min.y) min.y = p.y;
                if (p.y > max.y) max.y = p.y;

                if (p.z < min.z) min.z = p.z;
                if (p.z > max.z) max.z = p.z;
            }
        }
        
        virtual bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, AABB& output_box) const;

        vec3 get_normal() const { 
            return unit_vector(cross(v[2]-v[0], v[1]-v[0]));
        }

        vec3 get_vertices() const {
            return v[3];
        }

    private:
        vec3 v[3];
        shared_ptr<Material> mat_ptr;
        vec3 min, max; // For AABB

};

// ref: https://pheema.hatenablog.jp/entry/ray-tdriangle-intersection
bool Triangle::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const {
    float kEps = 1e-6f;

    vec3 e1 = v[1] - v[0];
    vec3 e2 = v[2] - v[0];

    vec3 alpha = cross(r.direction(), e2);
    float det = dot(e1, alpha);

    if(det < fabs(kEps)) return false;

    float invDet = 1.0 / det;
    vec3 ov0 = r.origin() - v[0];

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
    auto normal = unit_vector(cross(e2, e1));
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool Triangle::bounding_box(double t0, double t1, AABB& output_box) const {
    output_box = AABB(min, max);
    return true;
}

#endif