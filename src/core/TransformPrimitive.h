#pragma once

#include "Primitive.h"
#include "mat4.h"

class TransformPrimitive final : public Primitive {
public:
    TransformPrimitive(std::shared_ptr<Primitive> p) : p(p), mat(mat4()) {}
    TransformPrimitive(std::shared_ptr<Primitive> p, mat4 mat) : p(p), mat(mat.mat) {}
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override;

    void rotate_x(double theta);
    void rotate_y(double theta);
    void rotate_z(double theta);
    void rotate(double theta, const vec3& axis);

    void translate(const vec3& t);

    void scale(const vec3& s);
    void scale(double s);

private: 
    std::shared_ptr<Primitive> p;
    mat4 mat;
};

Ray transform(const Ray& r, const mat4& mat);

