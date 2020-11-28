#include "TransformPrimitive.h"

// ----------------------------------------------------------------------
bool TransformPrimitive::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // transformed ray
    Ray tr = transform_ray(r, this->mat);
    if(!p->intersect(tr, t_min, t_max, rec))
        return false;
    
    return true;
}

// ----------------------------------------------------------------------
AABB TransformPrimitive::bounding() const {
    auto min = p->bounding().min();
    auto max = p->bounding().max();

    // transformed min/max
    auto tr_min = this->mat * min;
    auto tr_max = this->mat * max;

    return AABB(tr_min, tr_max);
}

// ----------------------------------------------------------------------
void TransformPrimitive::rotate_x(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    this->mat = this->mat * mat4(1, 0, 0,  0,
                                 0, c, -s, 0,
                                 0, s, c,  0,
                                 0, 0, 0,  1);
}
void TransformPrimitive::rotate_y(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    this->mat = this->mat * mat4(c,  0, s, 0, 
                                 0,  1, 0, 0,
                                 -s, 0, c, 0,
                                 0,  0, 0, 1);
}
void TransformPrimitive::rotate_z(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    this->mat = this->mat * mat4(c, -s, 0, 0, 
                                 s, c,  0, 0,
                                 0, 0,  1, 0,
                                 0, 0,  0, 1);
}
void TransformPrimitive::rotate(double theta, const vec3& axis) {
    double sx = sin(theta) * axis.x;
    double cx = cos(theta) * axis.x;
    double sy = sin(theta) * axis.y;
    double cy = cos(theta) * axis.y;
    double sz = sin(theta) * axis.z;
    double cz = cos(theta) * axis.z;
    this->mat = this->mat * mat4(
        cy*cz, sx*sy*cz-sz*cx, sx*sz+cx*sy*cz, 0,
        cy*sz, cx*cz+sz*sy*sz, cx*sy*sz-sx*cz, 0,
        -sy,   sx*cy,          cx*cy,          0,
        0,     0,              0,              1
    );
}

// ----------------------------------------------------------------------
void TransformPrimitive::translate(const vec3& t) {
    this->mat.mat[0][3] += t.x;
    this->mat.mat[1][3] += t.y;
    this->mat.mat[2][3] += t.z;
}

// ----------------------------------------------------------------------
void TransformPrimitive::scale(const vec3& s) {
    this->mat = this->mat * mat4(s.x, 0,   0,   0,
                                 0,   s.y, 0,   0,
                                 0,   0,   s.z, 0,
                                 0,   0,   0,   1);
}
void TransformPrimitive::scale(double s) {
    this->mat = this->mat * mat4(s, 0, 0, 0,
                                 0, s, 0, 0,
                                 0, 0, s, 0,
                                 0, 0, 0, 1);
}

// ----------------------------------------------------------------------
Ray transform_ray(const Ray& r, const mat4& mat) {
    auto ro = mat * r.origin();
    auto rd = mat * r.direction();
    return Ray(ro, rd, r.time());
}