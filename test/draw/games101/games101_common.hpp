#ifndef GAMES101_COMMON_H
#define GAMES101_COMMON_H

#include <eigen3/Eigen/Eigen>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    float cos_theta = std::cos(rotation_angle / 180.0 * MY_PI);
    float sin_theta = std::sin(rotation_angle / 180.0 * MY_PI);

    Eigen::Matrix4f rotate_around_z_axis;    
    rotate_around_z_axis <<
        cos_theta, -sin_theta, 0.0, 0.0,
        sin_theta, cos_theta, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;

    model = rotate_around_z_axis * model;

    return model;
}

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate <<
        1, 0, 0, -eye_pos[0],
        0, 1, 0, -eye_pos[1],
        0, 0, 1, -eye_pos[2],
        0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar)
{

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    float l, r, b, t;

    float n = -zNear;
    float f = -zFar;

    t = -n * std::tan(eye_fov / 2 / 180.0 * MY_PI);
    b = -t;
    r = aspect_ratio * t;
    l = -r;

    Eigen::Matrix4f perspective_proj;
    perspective_proj <<
        2 * n / (r - l), 0.0, -(r + l) / (r - l), 0.0,
        0.0, 2 * n / (t - b), 0.0, -(t + b) / (t - b),
        0.0, 0.0, (n + f) / (n - f), -2 * n * f / (n - f),
        0.0, 0.0, 1.0, 0.0;

    projection = perspective_proj * projection;

    return projection;
}

#endif // GAMES101_COMMON_H