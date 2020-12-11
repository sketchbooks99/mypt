#include "mat4.h"
#include <string.h>

namespace mypt {

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

}