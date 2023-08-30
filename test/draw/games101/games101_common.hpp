#ifndef GAMES101_COMMON_H
#define GAMES101_COMMON_H

#include <eigen3/Eigen/Eigen>

#define WIDTH 800
#define HEIGHT 600

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

    // zNear, zFar are positive, and n, f are negative
    float n = -zNear;
    float f = -zFar;

    t = -n * std::tan(eye_fov / 2 / 180.0 * MY_PI);
    b = -t;
    r = aspect_ratio * t;
    l = -r;

    float p11 = 2 * n / (r - l);
    float p13 = -(r + l) / (r - l);
    float p22 = 2 * n / (t - b);
    float p23 = -(t + b) / (t - b);
    float p33 = (n + f) / (n - f);
    float p34 = -2 * n * f / (n - f);

    Eigen::Matrix4f perspective_proj;
    perspective_proj <<
        p11, 0.0, p13, 0.0,
        0.0, p22, p23, 0.0,
        0.0, 0.0, p33, p34,
        0.0, 0.0, 1.0, 0.0;

    projection = perspective_proj * projection;

    return projection;
}

float line_interpolation(float p, float p0, float p1, float a0, float a1) {
    float t = (p - p0) / (p1 - p0);
    return (1.0 - t) * a0 + t * a1;
}

void rasterize_line(Eigen::Vector4f v0, Eigen::Vector4f v1, uint8_t *color_buffer) {
    float v0_x = v0[0];
    float v1_x = v1[0];
    float v0_y = v0[1];
    float v1_y = v1[1];
    float line_dx = v1_x - v0_x;
    float line_dy = v1_y - v0_y;

    uint32_t start, end;

    if (fabs(line_dx) >= fabs(line_dy)) {
        // x-major
        if (v1_x >= v0_x) {
            start = (uint32_t)v0_x;
            end = (uint32_t)v1_x;
        } else {
            start = (uint32_t)v1_x;
            end = (uint32_t)v0_x;
        }

        for (uint32_t x = start; x <= end; x++) {
            uint32_t y = (uint32_t) line_interpolation(x, v0_x, v1_x, v0_y, v1_y);

            color_buffer[(y * WIDTH + x) * 4 + 0] = 255;
            color_buffer[(y * WIDTH + x) * 4 + 1] = 255;
            color_buffer[(y * WIDTH + x) * 4 + 2] = 255;
            color_buffer[(y * WIDTH + x) * 4 + 3] = 255;
        }
    } else {
        // y-major
        if (v1_y >= v0_y) {
            start = (uint32_t)v0_y;
            end = (uint32_t)v1_y;
        } else {
            start = (uint32_t)v1_y;
            end = (uint32_t)v0_y;
        }

        for (uint32_t y = start; y <= end; y++) {
            uint32_t x = (uint32_t) line_interpolation(y, v0_y, v1_y, v0_x, v1_x);

            color_buffer[(y * WIDTH + x) * 4 + 0] = 255;
            color_buffer[(y * WIDTH + x) * 4 + 1] = 255;
            color_buffer[(y * WIDTH + x) * 4 + 2] = 255;
            color_buffer[(y * WIDTH + x) * 4 + 3] = 255;
        }
    }
}

#endif // GAMES101_COMMON_H