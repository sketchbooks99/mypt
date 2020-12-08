#pragma once

#include "MathUtil.h"
#include "Ray.h"

struct Transform {
public:
    Transform() : mat(mat4()), matInv(mat4()) {}
    Transform(mat4 m) : mat(m.mat), matInv(inverse(m).mat) {}
    Transform(mat4 m, mat4 mInv) : mat(m.mat), matInv(mInv) {}

    mat4 getMatrix() { return mat; }
    mat4 getInvMatrix() { return matInv; }

    static Transform translate(vec3 t);

    static Transform rotateX(double theta);
    static Transform rotateY(double theta);
    static Transform rotateZ(double theta);
    static Transform rotate(double theta, vec3 axis);

    static Transform scale(double s);
    static Transform scale(vec3 s);

    mat4 mat, matInv;

};

inline Transform operator*(Transform t1, Transform t2) {
    auto mat = t1.mat * t2.mat;
    auto matInv = t2.matInv * t1.matInv;
    return Transform(mat, matInv);
}

inline Ray operator*(Transform t, Ray r) {
    vec3 ro = mat4::point_mul(t.getInvMatrix(), r.origin());
    /// MEMO: Normalize direction might cause scale error. 
    ///       I have to check non-normalize version. 
    // vec3 rd = normalize(mat4::vector_mul(t.getInvMatrix(), r.direction()));
    vec3 rd = mat4::vector_mul(t.getInvMatrix(), r.direction());
    return Ray(ro, rd);
}

class TransformSystem {
public:
    TransformSystem();
    TransformSystem(mat4 m);

    void pushMatrix();
    void popMatrix();

    Transform getCurrentTransform();

    std::vector<Transform> getTransformStack() { return transformStack; }

    void translate(vec3 t);

    void rotateX(double theta);
    void rotateY(double theta);
    void rotateZ(double theta);
    void rotate(double theta, vec3 axis);

    void scale(double s);
    void scale(vec3 s);

private:
    std::vector<Transform> transformStack;
};