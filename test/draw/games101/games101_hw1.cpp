#include "gpu_execuator.hpp"
#include "games101_common.hpp"
#include "games101_config.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>

TEST_F(GPUExecuator, games101_hw1) {
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



// --------------------



    // 2. Vertex shader
    Eigen::Vector4f vs_out_positions[3];

    LoadELF("games101", "games101_hw1_vertex_shader");
    PushParam(0); // tid
    PushParam((uint64_t)vertex_positions);
    PushParam((uint64_t)vs_out_positions);
    PushParam((uint64_t)(&model));
    PushParam((uint64_t)(&view));
    PushParam((uint64_t)(&projection));
    run1d(3);



// --------------------



    // 3. Rasterization
    uint8_t *color_buffer = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));

    float line_dx[3];
    float line_dy[3];
    uint8_t line_is_x_major[3];
    uint32_t line_start_x[3];
    uint32_t line_end_x[3];
    uint32_t line_start_y[3];
    uint32_t line_end_y[3];

    // Iterate over lines
    for (int i = 0; i < 3; i++) {
        line_dx[i] = vs_out_positions[(i + 1) % 3].x() - vs_out_positions[i % 3].x();
        line_dy[i] = vs_out_positions[(i + 1) % 3].y() - vs_out_positions[i % 3].y();

        line_is_x_major[i] = (fabs(line_dx[i]) >= fabs(line_dy[i]));

        if (line_dx[i] >= 0) {
            line_start_x[i] = (uint32_t)vs_out_positions[i % 3].x();
            line_end_x[i] = (uint32_t)vs_out_positions[(i + 1) % 3].x();
        } else {
            line_start_x[i] = (uint32_t)vs_out_positions[(i + 1) % 3].x();
            line_end_x[i] = (uint32_t)vs_out_positions[i % 3].x();
        }

        if (line_dy[i] >= 0) {
            line_start_y[i] = (uint32_t)vs_out_positions[i % 3].y();
            line_end_y[i] = (uint32_t)vs_out_positions[(i + 1) % 3].y();
        } else {
            line_start_y[i] = (uint32_t)vs_out_positions[(i + 1) % 3].y();
            line_end_y[i] = (uint32_t)vs_out_positions[i % 3].y();
        }

        // Finding the intersection point of a line and an axis is equivalent to doing line interpolation of attributes
        if (line_is_x_major[i]) {
            // x-major
            float p0 = vs_out_positions[i % 3].x();
            float p1 = vs_out_positions[(i + 1) % 3].x();
            float a0 = vs_out_positions[i % 3].y();
            float a1 = vs_out_positions[(i + 1) % 3].y();

            float line_endpoints[2] = {p0, p1};
            float line_attributes[2] = {a0, a1};

            LoadELF("games101", "games101_hw1_rasterization");
            PushParam(0); // tid
            PushParam((uint64_t)line_endpoints);
            PushParam((uint64_t)line_attributes);
            PushParam((uint64_t)color_buffer);
            PushParam((uint64_t)(&line_start_x[i]));
            PushParam((uint64_t)(&line_is_x_major[i]));
            run1d(line_end_x[i] - line_start_x[i] + 1);
        } else {
            // y-major
            float p0 = vs_out_positions[i % 3].y();
            float p1 = vs_out_positions[(i + 1) % 3].y();
            float a0 = vs_out_positions[i % 3].x();
            float a1 = vs_out_positions[(i + 1) % 3].x();

            float line_endpoints[2] = {p0, p1};
            float line_attributes[2] = {a0, a1};

            LoadELF("games101", "games101_hw1_rasterization");
            PushParam(0); // tid
            PushParam((uint64_t)line_endpoints);
            PushParam((uint64_t)line_attributes);
            PushParam((uint64_t)color_buffer);
            PushParam((uint64_t)(&line_start_y[i]));
            PushParam((uint64_t)(&line_is_x_major[i]));
            run1d(line_end_y[i] - line_start_y[i] + 1);
        }
    }



// --------------------



    // 4. Write to image
    uint8_t *image = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));

    uint32_t img_pid, cb_pid;

    for (uint32_t x = 0; x < WIDTH; x++) {
        for (uint32_t y = 0; y < HEIGHT; y++) {
            img_pid = y * WIDTH + x;
            cb_pid = (HEIGHT - 1 - y) * WIDTH + x;

            image[img_pid * 4 + 0] = color_buffer[cb_pid * 4 + 0];
            image[img_pid * 4 + 1] = color_buffer[cb_pid * 4 + 1];
            image[img_pid * 4 + 2] = color_buffer[cb_pid * 4 + 2];
            image[img_pid * 4 + 3] = color_buffer[cb_pid * 4 + 3];
        }
    }

    WritePPM("games101_hw1", WIDTH, HEIGHT, image);
}
