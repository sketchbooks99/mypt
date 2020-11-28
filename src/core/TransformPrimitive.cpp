#include "TransformPrimitive.h"

// ----------------------------------------------------------------------
bool TransformPrimitive::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // transformed ray
}

AABB TransformPrimitive::bounding() const {
    auto min = p->bounding().min();
    auto max = p->bounding().max();

    // transformed min/max
    auto tr_min = this->mat * min;
    auto tr_max = this->mat * max;

    return AABB(tr_min, tr_max);
}

void TransformPrimitive::rotate_x(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    this->mat = this->mat * mat4(1, 0, 0, 0,
                                 0, c, -s, 0,
                                 0, s, c, 0,
                                 0, 0, 0, 1);
}
void TransformPrimitive::rotate_y(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    this->mat = this->mat * mat4(c, 0, s, 0, 
                                 0, 1, 0, 0,
                                 -s, 0, c, 0,
                                 0, 0, 0, 1);
}
void TransformPrimitive::rotate_z(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    this->mat = this->mat * mat4(c, -s, 0, 0, 
                                 s, c, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1);
}
void TransformPrimitive::rotate(double theta, const vec3& axis) {

}

void TransformPrimitive::translate(const vec3& t) {

}

void TransformPrimitive::scale(const vec3& s) {

}
void TransformPrimitive::scale(double s) {

}

Ray transform(const mat4& mat, const Ray& r) {
    auto ro = mat * r.origin();
    auto rd = mat * r.direction();
    return Ray(ro, rd, r.time());
}