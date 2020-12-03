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
    transformStack.push_back(std::make_shared<Transform>());
}

TransformSystem::TransformSystem(mat4 m) {
    transformStack.push_back(std::make_shared<Transform>(m));
}

// ----------------------------------------------------------------------
void TransformSystem::pushMatrix() {
    ASSERT(transformStack.size() < 32, "The maximum number of matrices is 32\n");
    transformStack.push_back(std::make_shared<Transform>());
}

void TransformSystem::popMatrix() {
    ASSERT(transformStack.size() > 1, "Transform class must have at least 1 matrix.\n");
    transformStack.pop_back();
}

// ----------------------------------------------------------------------
Transform TransformSystem::getCurrentTransform() {
    return *transformStack.back();
}
std::shared_ptr<Transform> TransformSystem::getCurrentTransformPtr() {
    return transformStack.back();
}

// ----------------------------------------------------------------------
void TransformSystem::translate(vec3 t) {
    auto currentTransformPtr = getCurrentTransformPtr();
    *currentTransformPtr = *currentTransformPtr * Transform::translate(t);
}

void TransformSystem::rotateX(double theta) {
    auto currentTransformPtr = getCurrentTransformPtr();
    auto rotMatX = rotate_mat_x(theta);
    *currentTransformPtr = *currentTransformPtr * Transform::rotateX(theta);
}

void TransformSystem::rotateY(double theta) {
    auto currentTransformPtr = getCurrentTransformPtr();
    auto rotMatY = rotate_mat_y(theta);
    *currentTransformPtr = *currentTransformPtr * Transform::rotateY(theta);
}

void TransformSystem::rotateZ(double theta) {
    auto currentTransformPtr = getCurrentTransformPtr();
    auto rotMatZ = rotate_mat_z(theta);
    *currentTransformPtr = *currentTransformPtr * Transform::rotateZ(theta);
}

void TransformSystem::rotate(double theta, vec3 axis) {
    auto currentTransformPtr = getCurrentTransformPtr();
    *currentTransformPtr = *currentTransformPtr * Transform::rotate(theta, axis);
}

void TransformSystem::scale(double s) {
    auto currentTransformPtr = getCurrentTransformPtr();
    *currentTransformPtr = *currentTransformPtr * Transform::scale(s);
}

void TransformSystem::scale(vec3 s) {
    auto currentTransformPtr = getCurrentTransformPtr();
    *currentTransformPtr = *currentTransformPtr * Transform::scale(s);
}