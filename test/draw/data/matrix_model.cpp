#include <eigen3/Eigen/Eigen>

constexpr double MY_PI = 3.1415926;

extern "C" {

void gpumain(long tid, float *out) {
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    float cos_theta = std::cos(20.0 / 180.0 * MY_PI);
    float sin_theta = std::sin(20.0 / 180.0 * MY_PI);

    Eigen::Matrix4f rotate_around_z_axis;    
    rotate_around_z_axis <<
        cos_theta, -sin_theta, 0.0, 0.0,
        sin_theta, cos_theta, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;

    model = rotate_around_z_axis * model;

    for (int i=0; i<16; i++) {
        out[i] = model.data()[i];
    }
}
}
