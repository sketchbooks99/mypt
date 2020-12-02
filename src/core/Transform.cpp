#include "Transform.h"

// ----------------------------------------------------------------------
Transform::Transform() {
    matrices.push_back(std::make_shared<mat4>());
    invMatrices.push_back(std::make_shared<mat4>());
}

Transform::Transform(mat4 m) {
    matrices.push_back(std::make_shared<mat4>(m.mat));
    invMatrices.push_back(std::make_shared<mat4>(inverse(m).mat));
}

// ----------------------------------------------------------------------
void Transform::pushMatrix() {
    ASSERT(matrices.size() < 32, "The maximum number of matrices is 32\n");
    matrices.push_back(std::make_shared<mat4>());
    invMatrices.push_back(std::make_shared<mat4>());
}

void Transform::popMatrix() {
    ASSERT(matrices.size() > 1, "Transform class must have at least 1 matrix.\n");
    matrices.pop_back();
    invMatrices.pop_back();
}

// ----------------------------------------------------------------------
mat4 Transform::getCurrentMatrix() {
    return *matrices.back();
}
std::shared_ptr<mat4> Transform::getCurrentMatrixPtr() {
    return matrices.back();
}
mat4 Transform::getCurrentInvMatrix() {
    return *invMatrices.back();
}
std::shared_ptr<mat4> Transform::getCurrentInvMatrixPtr() {
    return invMatrices.back();
}

// ----------------------------------------------------------------------
void Transform::translate(vec3 t) {
    auto currentMat = getCurrentMatrixPtr();
    *currentMat = *currentMat * translate_mat(t);
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = translate_mat(-t) * *currentMatInv;
}

void Transform::rotateX(double theta) {
    auto currentMat = getCurrentMatrixPtr();;
    auto rotMatX = rotate_mat_x(theta);
    *currentMat = *currentMat * rotMatX;
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = transpose(rotMatX) * *currentMatInv;
}

void Transform::rotateY(double theta) {
    auto currentMat = getCurrentMatrixPtr();;
    auto rotMatX = rotate_mat_y(theta);
    *currentMat = *currentMat * rotMatX;
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = transpose(rotMatX) * *currentMatInv;
}

void Transform::rotateZ(double theta) {
    auto currentMat = getCurrentMatrixPtr();;
    auto rotMatX = rotate_mat_z(theta);
    *currentMat = *currentMat * rotMatX;
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = transpose(rotMatX) * *currentMatInv;
}

void Transform::rotate(double theta, vec3 axis) {
    auto currentMat = getCurrentMatrixPtr();
    auto rotMat = rotate_mat(theta, axis);
    *currentMat = *currentMat * rotMat;
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = transpose(rotMat) * *currentMatInv;
}

void Transform::scale(double s) {
    auto currentMat = getCurrentMatrixPtr();
    *currentMat = *currentMat * scale_mat(s);
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = scale_mat(1.0f / s) * *currentMatInv;
}

void Transform::scale(vec3 s) {
    auto currentMat = getCurrentMatrixPtr();
    *currentMat = *currentMat * scale_mat(s);
    auto currentMatInv = getCurrentInvMatrixPtr();
    *currentMatInv = scale_mat(vec3(1.0f/s.x, 1.0f/s.y, 1.0f/s.z)) * *currentMatInv;
}