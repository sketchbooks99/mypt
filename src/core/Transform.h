#pragma once

#include "math_util.h"
#include "ray.h"

namespace mypt {

struct Transform {
public:
    Transform() : mat(mat4()), matInv(mat4()) {}
    explicit Transform(mat4 m) : mat(m.mat), matInv(inverse(m).mat) {}
    explicit Transform(mat4 m, mat4 mInv) : mat(m.mat), matInv(mInv) {}

    mat4 getMatrix() { return mat; }
    mat4 getInvMatrix() { return matInv; }

    static Transform translate(vec3 t);

    static Transform rotateX(Float theta);
    static Transform rotateY(Float theta);
    static Transform rotateZ(Float theta);
    static Transform rotate(Float theta, vec3 axis);

    static Transform scale(Float s);
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
    vec3 rd = mat4::vector_mul(t.getInvMatrix(), r.direction());
    return Ray(ro, rd);
}

class TransformSystem {
public:
    TransformSystem();
    explicit TransformSystem(mat4 m);

    void pushMatrix();
    void popMatrix();

    Transform getCurrentTransform();

    std::vector<Transform> getTransformStack() { return transformStack; }

    void translate(vec3 t);

    void rotateX(Float theta);
    void rotateY(Float theta);
    void rotateZ(Float theta);
    void rotate(Float theta, vec3 axis);

    void scale(Float s);
    void scale(vec3 s);

private:
    std::vector<Transform> transformStack;
};

}