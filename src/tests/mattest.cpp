#include "../core/MathUtil.h"

int main(void) {
    vec3 vec(5,6,7);

    double theta = pi / 3.0f;
    mat4 r_mat = rotate_mat(theta, vec3(1, 1, 1));
    mat4 rx_mat = rotate_mat_x(theta);
    mat4 ry_mat = rotate_mat_y(theta);
    mat4 rz_mat = rotate_mat_z(theta);
    std::cout << "----- rotate test -----" << std::endl;
    std::cout << r_mat * vec << std::endl;
    std::cout << rx_mat * vec << std::endl;
    std::cout << ry_mat * vec << std::endl;
    std::cout << rz_mat * vec << std::endl;

    mat4 tr_mat = translate_mat(vec3(3,4,5));
    std::cout << "----- translate test -----" << std::endl;
    std::cout << tr_mat * vec << std::endl;

    std::cout << "----- scale test -----" << std::endl;
    mat4 s_mat1 = scale_mat(vec3(1,2,3));
    mat4 s_mat2 = scale_mat(3.0);
    std::cout << s_mat1 * vec << std::endl;
    std::cout << s_mat2 * vec << std::endl;

    return 0;
}