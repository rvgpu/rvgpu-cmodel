#include "gpu_execuator.hpp"
#include "games101_common.hpp"
#include "games101_config.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>

#include "data/games101_hw2_vertex_shader.hpp"
#include "data/games101_hw2_rasterization.hpp"

#define VERTEX_COUNT 6
#define TRIANGLE_COUNT (VERTEX_COUNT / 3)

TEST_F(GPUExecuator, games101_hw2) {
    // 1. Data preparation
    // 1.1 Vertices
    Eigen::Vector3f vertex_positions[VERTEX_COUNT] = {
        {2, 0, -2},
        {0, 2, -2},
        {-2, 0, -2},
        {3.5, -1, -5},
        {2.5, 1.5, -5},
        {-1, 0.5, -5}
    };
    Eigen::Vector3f vertex_colors[VERTEX_COUNT] = {
        {217.0, 238.0, 185.0},
        {217.0, 238.0, 185.0},
        {217.0, 238.0, 185.0},
        {185.0, 217.0, 238.0},
        {185.0, 217.0, 238.0},
        {185.0, 217.0, 238.0}
    };
    
    // 1.2 Matrices
    float angle = 0;
    Eigen::Vector3f eye_pos = {0, 0, 5};

    Eigen::Matrix4f model = get_model_matrix(angle);
    Eigen::Matrix4f view = get_view_matrix(eye_pos);
    Eigen::Matrix4f projection = get_projection_matrix(45, 1, 0.1, 50);



// --------------------



    // 2. Vertex shader
    Eigen::Vector4f vs_out_positions[VERTEX_COUNT];

#if RUN_ON_GPU
    LoadELF("games101", "games101_hw2_vertex_shader");
    PushParam(0); // tid
    PushParam((uint64_t)vertex_positions);
    PushParam((uint64_t)vs_out_positions);
    PushParam((uint64_t)(&model));
    PushParam((uint64_t)(&view));
    PushParam((uint64_t)(&projection));
    run1d(VERTEX_COUNT);
#else
    for (long tid = 0; tid < VERTEX_COUNT; tid++) {
        vertex_shader(tid, vertex_positions, vs_out_positions, &model, &view, &projection);
    }
#endif


// --------------------



    // 3. Rasterization
    struct triangle triangles[TRIANGLE_COUNT];

    for (int i = 0; i < TRIANGLE_COUNT; i++) {
        for (int j = 0; j < 3; j++) {
            triangles[i].v[j] = vs_out_positions[(i * 3) + j];
            triangles[i].color[j] = vertex_colors[(i * 3) + j];
        }        
    }

    uint8_t *color_buffer = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));
    float *depth_buffer = (float *) calloc(WIDTH * HEIGHT, sizeof(float));

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        depth_buffer[i] = -1.0f;
    }

    // Iterate over triangles    
    for (int i = 0; i < TRIANGLE_COUNT; i++) {
        struct triangle t = triangles[i];

        Eigen::Vector3f triangle_x(t.v[0].x(), t.v[1].x(), t.v[2].x());
        Eigen::Vector3f triangle_y(t.v[0].y(), t.v[1].y(), t.v[2].y());

        // Bounding box
        uint32_t box_l = (uint32_t)triangle_x.minCoeff();
        uint32_t box_r = (uint32_t)triangle_x.maxCoeff() + 1;
        uint32_t box_b = (uint32_t)triangle_y.minCoeff();
        uint32_t box_t = (uint32_t)triangle_y.maxCoeff() + 1;

        uint32_t box_width = box_r - box_l;
        uint32_t box_height = box_t - box_b;

        struct box_info box = {box_l, box_b, box_width};
        
        // Iterate over bounding box
#if RUN_ON_GPU
        LoadELF("games101", "games101_hw2_rasterization");
        PushParam(0); // tid
        PushParam((uint64_t)(&t));
        PushParam((uint64_t)color_buffer);
        PushParam((uint64_t)depth_buffer);
        PushParam((uint64_t)(&box));
        run1d(box_width * box_height);
#else
        for (long tid = 0; tid < box_width * box_height; tid++) {
            rasterization(tid, &t, color_buffer, depth_buffer, &box);
        }
#endif
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

    WritePPM("games101_hw2", WIDTH, HEIGHT, image);
}
