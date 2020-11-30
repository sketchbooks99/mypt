#pragma once

#include "MathUtil.h"

class Transform {
public:
    Transform();
    Transform(mat4 m);

    void pushMatrix();
    void popMatrix();

    std::shared_ptr<mat4> getCurrentMatrixPtr();
    std::shared_ptr<mat4> getCurrentInvMatrixPtr();

    mat4 getCurrentMatrix();
    mat4 getCurrentInvMatrix();

    void translate(vec3 t);

    void rotateX(double theta);
    void rotateY(double theta);
    void rotateZ(double theta);
    void rotate(double theta, vec3 axis);

    void scale(double s);
    void scale(vec3 s);
    
private:
    std::vector<std::shared_ptr<mat4>> matrices;
    std::vector<std::shared_ptr<mat4>> invMatrices;
};