#include "Transform.h"

// Transform ------------------------------------------------------------
Transform Transform::translate(vec3 t) {
    return Transform(translate_mat(t), translate_mat(-t));
}

Transform Transform::rotateX(double theta) {
    return Transform(rotate_mat_x(theta), transpose(rotate_mat_x(theta)));
}
Transform Transform::rotateY(double theta) {
    return Transform(rotate_mat_y(theta), transpose(rotate_mat_y(theta)));
}
Transform Transform::rotateZ(double theta) {
    return Transform(rotate_mat_z(theta), transpose(rotate_mat_z(theta)));
}
Transform Transform::rotate(double theta, vec3 axis) {
    return Transform(rotate_mat(theta, axis), transpose(rotate_mat(theta, axis)));
}

Transform Transform::scale(double s) {
    ASSERT(s != 0, "Scale value must be non-zero!\n");
    return Transform(scale_mat(s), scale_mat(1.0f / s));
}
Transform Transform::scale(vec3 s) {
    ASSERT(s.x != 0 && s.y != 0 && s.z != 0, "Scale value must be non-zero!\n");
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
    ASSERT(transformStack.size() < 32, "The maximum number of matrices is 32\n");
    transformStack.push_back(Transform());
}

void TransformSystem::popMatrix() {
    ASSERT(transformStack.size() > 1, "Transform class must have at least 1 matrix.\n");
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

void TransformSystem::rotateX(double theta) {
    transformStack.back() = transformStack.back() * Transform::rotateX(theta);
}

void TransformSystem::rotateY(double theta) {
    transformStack.back() = transformStack.back() * Transform::rotateY(theta);
}

void TransformSystem::rotateZ(double theta) {
    transformStack.back() = transformStack.back() * Transform::rotateZ(theta);
}

void TransformSystem::rotate(double theta, vec3 axis) {
    transformStack.back() = transformStack.back() * Transform::rotate(theta, axis);
}

void TransformSystem::scale(double s) {
    transformStack.back() = transformStack.back() * Transform::scale(s);
}

void TransformSystem::scale(vec3 s) {
    transformStack.back() = transformStack.back() * Transform::scale(s);
}