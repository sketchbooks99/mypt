#pragma once

#include "vec.h"

namespace mypt {

struct mat4 {
    explicit mat4();
    explicit mat4(Float m[4][4]);
    mat4(Float e00, Float e01, Float e02, Float e03,
         Float e10, Float e11, Float e12, Float e13,
         Float e20, Float e21, Float e22, Float e23,
         Float e30, Float e31, Float e32, Float e33);

    // Multiply matrix(4x4) with vector
    inline static vec3 vector_mul(const mat4& m, const vec3& v) {
        Float x = v.x, y = v.y, z = v.z;
        return vec3(m.mat[0][0]*x + m.mat[0][1]*y + m.mat[0][2]*z,
                    m.mat[1][0]*x + m.mat[1][1]*y + m.mat[1][2]*z,
                    m.mat[2][0]*x + m.mat[2][1]*y + m.mat[2][2]*z);
    }

    // Multiply matrix(4x4) with positional vector
    inline static vec3 point_mul(const mat4& m, const vec3& p) {
        Float x = m.mat[0][0]*p.x + m.mat[0][1]*p.y + m.mat[0][2]*p.z + m.mat[0][3];
        Float y = m.mat[1][0]*p.x + m.mat[1][1]*p.y + m.mat[1][2]*p.z + m.mat[1][3];
        Float z = m.mat[2][0]*p.x + m.mat[2][1]*p.y + m.mat[2][2]*p.z + m.mat[2][3];
        Float w = m.mat[3][0]*p.x + m.mat[3][1]*p.y + m.mat[3][2]*p.z + m.mat[3][3];
        Assert(w != 0, "This mat4 doesn't have proper value!\n");
        if(w == 1) {
            return vec3(x, y, z);
        } else {
            return vec3(x, y, z) / w;
        }
    }

    // Multiply matrix(4x4) with normal vector
    inline static vec3 normal_mul(const mat4& m, const vec3& n) {
        Float x = n.x, y = n.y, z = n.z;
        return vec3(m.mat[0][0]*x + m.mat[1][0]*y + m.mat[2][0]*z,
                    m.mat[0][1]*x + m.mat[1][1]*y + m.mat[2][1]*z,
                    m.mat[0][2]*x + m.mat[1][2]*y + m.mat[2][2]*z);
    }

    Float mat[4][4];
};

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
inline std::ostream& operator<<(std::ostream &out, const mat4 &m) {
    return out << "[ " << m.mat[0][0] << ' ' << m.mat[0][1] << ' ' << m.mat[0][2] << ' ' << m.mat[0][3] << '\n' \
               << "  " << m.mat[1][0] << ' ' << m.mat[1][1] << ' ' << m.mat[1][2] << ' ' << m.mat[1][3] << '\n' \
               << "  " << m.mat[2][0] << ' ' << m.mat[2][1] << ' ' << m.mat[2][2] << ' ' << m.mat[2][3] << '\n' \
               << "  " << m.mat[3][0] << ' ' << m.mat[3][1] << ' ' << m.mat[3][2] << ' ' << m.mat[3][3] << " ]";
}

// ----------------------------------------------------------------------
inline mat4 inverse(mat4 m) {
    mat4 inv;
    Float tmp;
    for(int i=0; i<4; i++) {
        tmp = 1.0 / m.mat[i][i];
        for(int j=0; j<4; j++) {
            m.mat[i][j] *= tmp;
            inv.mat[i][j] *= tmp;
        }
        for(int j=0; j<4; j++) {
            if(i != j) {
                tmp = m.mat[j][i];
                for(int k=0; k<4; k++) {
                    m.mat[j][k] -= m.mat[i][k]*tmp;
                    inv.mat[j][k] -= inv.mat[i][k]*tmp;
                }
            }
        }
    }
    return inv;
}

inline mat4 transpose(const mat4& m) {
    return mat4(
        m.mat[0][0], m.mat[1][0], m.mat[2][0], m.mat[3][0],
        m.mat[0][1], m.mat[1][1], m.mat[2][1], m.mat[3][1],
        m.mat[0][2], m.mat[1][2], m.mat[2][2], m.mat[3][2],
        m.mat[0][3], m.mat[1][3], m.mat[2][3], m.mat[3][3]
    );
}

// ----------------------------------------------------------------------
inline mat4 rotate_mat_x(Float theta) {
    Float c = cos(theta);
    Float s = sin(theta);
    return mat4(1, 0, 0,  0,
                0, c, -s, 0,
                0, s, c,  0,
                0, 0, 0,  1);
}

inline mat4 rotate_mat_y(Float theta) {
    Float c = cos(theta);
    Float s = sin(theta);
    return mat4(c,  0, s, 0, 
                0,  1, 0, 0,
                -s, 0, c, 0,
                0,  0, 0, 1);
}

inline mat4 rotate_mat_z(Float theta) {
    Float c = cos(theta);
    Float s = sin(theta);
    return mat4(c, -s, 0, 0, 
                s, c,  0, 0,
                0, 0,  1, 0,
                0, 0,  0, 1);
}

inline mat4 rotate_mat(Float theta, const vec3& axis) {
    vec3 a = normalize(axis);
    Float s = sin(theta);
    Float c = cos(theta);
    mat4 m;
    m.mat[0][0] = a.x * a.x + (1 - a.x * a.x) * c;
    m.mat[0][1] = a.x * a.y * (1 - c) - a.z * s;
    m.mat[0][2] = a.x * a.z * (1 - c) + a.y * s;
    m.mat[0][3] = 0.0;

    m.mat[1][0] = a.x * a.y * (1 - c) + a.z * s;
    m.mat[1][1] = a.y * a.y + (1 - a.y * a.y) * c;
    m.mat[1][2] = a.y * a.z * (1 - c) - a.x * s;
    m.mat[1][3] = 0.0;

    m.mat[2][0] = a.x * a.z * (1 - c) - a.y * s;
    m.mat[2][1] = a.y * a.z * (1 - c) + a.x * s;
    m.mat[2][2] = a.z * a.z + (1 - a.z * a.z) * c;
    m.mat[2][3] = 0.0;

    return m;
}

// ----------------------------------------------------------------------
inline mat4 translate_mat(const vec3& t) {
    return mat4(
        1, 0, 0, t.x,
        0, 1, 0, t.y,
        0, 0, 1, t.z,
        0, 0, 0, 1
    );
}

// ----------------------------------------------------------------------
inline mat4 scale_mat(const vec3& s) {
    return mat4(
        s.x, 0,   0,   0,
        0,   s.y, 0,   0, 
        0,   0,   s.z, 0, 
        0,   0,   0,   1
    );
}

inline mat4 scale_mat(Float s) {
    return mat4(
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, s, 0,
        0, 0, 0, 1
    );
}

}