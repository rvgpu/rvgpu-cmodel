#ifndef GAMES101_REFERENCE_HW1_HPP
#define GAMES101_REFERENCE_HW1_HPP

#include "games101_common.hpp"
#include <eigen3/Eigen/Eigen>

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

uint8_t * games101_hw1_reference() {
    // 1. Data preparation
    // 1.1 Vertices
    Eigen::Vector3f vertex_positions[3] = {
        {2, 0, -2},
        {0, 2, -2},
        {-2, 0, -2}
    };
    
    // 1.2 Matrices
    float angle = 20;
    Eigen::Vector3f eye_pos = {0, 0, 5};

    Eigen::Matrix4f model = get_model_matrix(angle);
    Eigen::Matrix4f view = get_view_matrix(eye_pos);
    Eigen::Matrix4f projection = get_projection_matrix(45, 1, 0.1, 50);

    // 2. Vertex shader
    Eigen::Vector4f vs_out_positions[3];

    // 2.1 MVP
    for (int i = 0; i < 3; i++) {
        Eigen::Vector4f pos;
        pos << vertex_positions[i], 1.0;

        vs_out_positions[i] = projection * view * model * pos;
    }

    // 2.2 Homogeneous division
    for (int i = 0; i < 3; i++) {
        vs_out_positions[i][0] /= vs_out_positions[i][3];
        vs_out_positions[i][1] /= vs_out_positions[i][3];
        vs_out_positions[i][2] /= vs_out_positions[i][3];
    }

    // 2.3 Viewport transform
    for (int i = 0; i < 3; i++) {
        // (x, y) is in the screen space
        float x = vs_out_positions[i][0] * (WIDTH / 2) + (WIDTH / 2);
        float y = vs_out_positions[i][1] * (HEIGHT / 2) + (HEIGHT / 2);

        // z is between 0.0 and 1.0
        float z = vs_out_positions[i][2];

        // w is the original z before perspective projection
        float w = vs_out_positions[i][3];

        Eigen::Vector4f xyzw;
        xyzw << x, y, z, w;

        vs_out_positions[i] = xyzw;
    }

    // 3. Rasterization
    uint8_t *color_buffer = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));

    rasterize_line(vs_out_positions[0], vs_out_positions[1], color_buffer);
    rasterize_line(vs_out_positions[1], vs_out_positions[2], color_buffer);
    rasterize_line(vs_out_positions[2], vs_out_positions[0], color_buffer);

    return color_buffer;
}

#endif // GAMES101_REFERENCE_HW1_HPP