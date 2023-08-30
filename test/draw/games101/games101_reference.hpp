#ifndef GAMES101_REFERENCE_H
#define GAMES101_REFERENCE_H

#include <eigen3/Eigen/Eigen>
#include "games101_common.hpp"

#define WIDTH 800
#define HEIGHT 600

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
        float x = vs_out_positions[i][0] * (WIDTH / 2) + (WIDTH / 2);
        float y = vs_out_positions[i][1] * (HEIGHT / 2) + (HEIGHT / 2);
        float z = vs_out_positions[i][2];
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

#endif // GAMES101_REFERENCE_H