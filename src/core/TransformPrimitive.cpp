#include "TransformPrimitive.h"

// ----------------------------------------------------------------------
bool TransformPrimitive::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // transformed ray
    Ray tr = transform_ray(r, this->matInv);
    if(!p->intersect(tr, t_min, t_max, rec))
        return false;
    
    return true;
}

// ----------------------------------------------------------------------
AABB TransformPrimitive::bounding() const {
    vec3 min(infinity, infinity, infinity);
    vec3 max(-infinity, -infinity, -infinity);

    for(int i=0; i<2; i++) {            // 0: min.x, 1: max.x
        for(int j=0; j<2; j++) {        // 0: min.y, 1: max.y
            for(int k=0; k<2; k++) {    // 0: min.z, 1: max.z

                auto x = (1-i)*p->bounding().min().x + i*p->bounding().max().x;
                auto y = (1-j)*p->bounding().min().y + j*p->bounding().max().y;
                auto z = (1-k)*p->bounding().min().z + k*p->bounding().max().z;

                // Update min, and bounding box by transformed vector
                auto tr_corner = this->mat * vec3(x, y, z);
                for(int l=0; l<3; l++) {
                    min[l] = fmin(min[l], tr_corner[l]);
                    max[l] = fmax(max[l], tr_corner[l]);
                }
            } 
        }
    }

    return AABB(min, max);
}

// ----------------------------------------------------------------------
void TransformPrimitive::rotate_x(double theta) {
    mat4 rotmat_x = rotate_mat_x(theta);
    this->mat = this->mat * rotmat_x;
    this->matInv = inverse(rotmat_x) * this->matInv;
}
void TransformPrimitive::rotate_y(double theta) {
    mat4 rotmat_y = rotate_mat_y(theta);
    this->mat = this->mat * rotmat_y;
    this->matInv = inverse(rotmat_y) * this->matInv;
}
void TransformPrimitive::rotate_z(double theta) {
    mat4 rotmat_z = rotate_mat_z(theta);
    this->mat = this->mat * rotmat_z;
    this->matInv = inverse(rotmat_z) * this->matInv;
}
void TransformPrimitive::rotate(double theta, const vec3& axis) {
    mat4 rotmat = rotate_mat(theta, axis);
    this->mat = this->mat * rotmat;
    this->matInv = inverse(rotmat) * this->matInv;
}

// ----------------------------------------------------------------------
void TransformPrimitive::translate(const vec3& t) {
    mat4 trmat = translate_mat(t);
    this->mat = this->mat * trmat;
    this->matInv = inverse(trmat) * this->matInv;
}

// ----------------------------------------------------------------------
void TransformPrimitive::scale(const vec3& s) {
    mat4 smat = scale_mat(s);
    this->mat = this->mat * scale_mat(s);
    this->matInv = inverse(smat) * this->matInv;
}
void TransformPrimitive::scale(double s) {
    mat4 smat = scale_mat(s);
    this->mat = this->mat * scale_mat(s);
    this->matInv = inverse(smat) * this->matInv;
}

// ----------------------------------------------------------------------
Ray transform_ray(const Ray& r, const mat4& mat) {
    vec3 ro = mat * r.origin();
    vec3 rd = mat * r.direction() - vec3(mat.mat[0][3], mat.mat[1][3], mat.mat[2][3]);
    return Ray(ro, rd);
}