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

mat4::mat4(Float m[4][4]) { memcpy(mat, m, 16*sizeof(Float)); }

mat4::mat4(
    Float e00, Float e01, Float e02, Float e03,
    Float e10, Float e11, Float e12, Float e13,
    Float e20, Float e21, Float e22, Float e23,
    Float e30, Float e31, Float e32, Float e33
) {
    mat[0][0] = e00; mat[0][1] = e01; mat[0][2] = e02; mat[0][3] = e03;
    mat[1][0] = e10; mat[1][1] = e11; mat[1][2] = e12; mat[1][3] = e13;
    mat[2][0] = e20; mat[2][1] = e21; mat[2][2] = e22; mat[2][3] = e23;
    mat[3][0] = e30; mat[3][1] = e31; mat[3][2] = e32; mat[3][3] = e33;
}

}