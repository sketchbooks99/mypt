#include "transform.h"

namespace mypt {

// Transform ------------------------------------------------------------
Transform Transform::translate(vec3 t) {
    return Transform(translate_mat(t), translate_mat(-t));
}

Transform Transform::rotateX(Float theta) {
    return Transform(rotate_mat_x(theta), transpose(rotate_mat_x(theta)));
}
Transform Transform::rotateY(Float theta) {
    return Transform(rotate_mat_y(theta), transpose(rotate_mat_y(theta)));
}
Transform Transform::rotateZ(Float theta) {
    return Transform(rotate_mat_z(theta), transpose(rotate_mat_z(theta)));
}
Transform Transform::rotate(Float theta, vec3 axis) {
    return Transform(rotate_mat(theta, axis), transpose(rotate_mat(theta, axis)));
}

Transform Transform::scale(Float s) {
    Assert(s != 0, "Scale value must be non-zero!\n");
    return Transform(scale_mat(s), scale_mat(1.0f / s));
}
Transform Transform::scale(vec3 s) {
    Assert(s.x != 0 && s.y != 0 && s.z != 0, "Scale value must be non-zero!\n");
    return Transform(scale_mat(s), scale_mat(vec3(1.0f/s.x, 1.0f/s.y, 1.0f/s.z)));
}

// TransformSystem ------------------------------------------------------
TransformSystem::TransformSystem() {
    transformStack.push_back(Transform());
}

TransformSystem::TransformSystem(mat4 m) {
    transformStack.push_back(Transform(m));
}

// ----------------------------------------------------------------------
void TransformSystem::pushMatrix() {
    Assert(transformStack.size() < 32, "The maximum number of matrices is 32\n");
    transformStack.push_back(getCurrentTransform());
}

void TransformSystem::popMatrix() {
    Assert(transformStack.size() > 1, "Transform class must have at least 1 matrix.\n");
    transformStack.pop_back();
}

// ----------------------------------------------------------------------
Transform TransformSystem::getCurrentTransform() {
    return transformStack.back();
}

// ----------------------------------------------------------------------
void TransformSystem::translate(vec3 t) {
    transformStack.back() = transformStack.back() * Transform::translate(t);
}

void TransformSystem::rotateX(Float theta) {
    transformStack.back() = transformStack.back() * Transform::rotateX(theta);
}

void TransformSystem::rotateY(Float theta) {
    transformStack.back() = transformStack.back() * Transform::rotateY(theta);
}

void TransformSystem::rotateZ(Float theta) {
    transformStack.back() = transformStack.back() * Transform::rotateZ(theta);
}

void TransformSystem::rotate(Float theta, vec3 axis) {
    transformStack.back() = transformStack.back() * Transform::rotate(theta, axis);
}

void TransformSystem::scale(Float s) {
    transformStack.back() = transformStack.back() * Transform::scale(s);
}

void TransformSystem::scale(vec3 s) {
    transformStack.back() = transformStack.back() * Transform::scale(s);
}

}