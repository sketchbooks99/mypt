#include "mat4.h"
#include <string.h>

// ----------------------------------------------------------------------
inline mat4 operator*(const mat4& m1, const mat4& m2) {
    mat4 m;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            m.mat[i][j] = m1.mat[i][0]*m2.mat[0][j];
            m.mat[i][j] += m1.mat[i][1]*m2.mat[1][j];
            m.mat[i][j] += m1.mat[i][2]*m2.mat[2][j];
            m.mat[i][j] += m1.mat[i][3]*m2.mat[3][j];
        }
    }
    return m;
}

// ----------------------------------------------------------------------
mat4::mat4() {
    mat[0][0] = 1.0; mat[0][1] = 0.0; mat[0][2] = 0.0; mat[0][3] = 0.0;
    mat[1][0] = 0.0; mat[1][1] = 1.0; mat[1][2] = 0.0; mat[1][3] = 0.0;
    mat[2][0] = 0.0; mat[2][1] = 0.0; mat[2][2] = 1.0; mat[2][3] = 0.0;
    mat[3][0] = 0.0; mat[3][1] = 0.0; mat[3][2] = 0.0; mat[3][3] = 1.0;
}

mat4::mat4(double m[4][4]) { memcpy(mat, m, 16*sizeof(double)); }

mat4::mat4(
    double e00, double e01, double e02, double e03,
    double e10, double e11, double e12, double e13,
    double e20, double e21, double e22, double e23,
    double e30, double e31, double e32, double e33
) {
    mat[0][0] = e00; mat[0][1] = e01; mat[0][2] = e02; mat[0][3] = e03;
    mat[1][0] = e10; mat[1][1] = e11; mat[1][2] = e12; mat[1][3] = e13;
    mat[2][0] = e20; mat[2][1] = e21; mat[2][2] = e22; mat[2][3] = e23;
    mat[3][0] = e30; mat[3][1] = e31; mat[3][2] = e32; mat[3][3] = e33;
}

// ----------------------------------------------------------------------
void mat4::rotate_x(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    *this *= mat4(1, 0, 0, 0,
                  0, c, -s, 0,
                  0, s, c, 0, 
                  0, 0, 0, 1);
}

void mat4::rotate_y(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    *this *= mat4(c, 0, s, 0,
                  0, 1, 0, 0,
                  -s, 0, c, 0, 
                  0, 0, 0, 1);
}

void  mat4::rotate_z(double theta) {
    double c = cos(theta);
    double s = sin(theta);
    *this *= mat4(c, -s, 0, 0,
                  s, c, 0, 0,
                  0, 0, 1, 0, 
                  0, 0, 0, 1);
}

void mat4::rotate(double theta, const vec3& axis) {
    double sx = sin(theta) * axis.x;
    double cx = cos(theta) * axis.x;
    double sy = sin(theta) * axis.y;
    double cy = cos(theta) * axis.y;
    double sz = sin(theta) * axis.z;
    double cz = cos(theta) * axis.z;
    *this *= mat4(
        cy*cz, sx*sy*cz-sz*cx, sx*sz+cx*sy*cz, 0,
        cy*sz, cx*cz+sz*sy*sz, cx*sy*sz-sx*cz, 0,
        -sy,   sx*cy,          cx*cy,          0,
        0,     0,              0,              1
    );
}

// ----------------------------------------------------------------------
void mat4::translate(const vec3& t) {
    mat[0][3] += t.x;
    mat[1][3] += t.y;
    mat[2][3] += t.z;
}

// ----------------------------------------------------------------------
void mat4::scale(const vec3& s) {
    *this *= mat4(s.x, 0, 0, 0,
                  0, s.y, 0, 0,
                  0, 0, s.z, 0,
                  0, 0, 0, 1);
}

void mat4::scale(double s) {
    *this *= mat4(s, 0, 0, 0,
                  0, s, 0, 0,
                  0, 0, s, 0,
                  0, 0, 0, 1);
}


