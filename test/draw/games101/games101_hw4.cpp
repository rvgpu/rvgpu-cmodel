#include "gpu_execuator.hpp"
#include "games101_config.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>

#include "data/games101_hw4_naive_bazier.hpp"

TEST_F(GPUExecuator, games101_hw4) {
    // 1. Data preparation
    Eigen::Vector2f vertex_positions[4] = {
        {154.0f, 323.0f},
        {320.0f, 200.0f},
        {541.0f, 331.0f},
        {524.0f, 526.0f}
    };
    
    

// --------------------



    // 2. Rasterization
    uint8_t *color_buffer = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));

#if RUN_ON_GPU
    LoadELF("games101", "games101_hw4_naive_bazier");
    PushParam(0); // tid
    PushParam((uint64_t)vertex_positions);
    PushParam((uint64_t)color_buffer);
    run1d(1000);
#else
    for (long tid = 0; tid < 1000; tid++) {
        naive_bazier(tid, vertex_positions, color_buffer);
    }
#endif
    


// --------------------



    // 3. Write to image
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

    WritePPM("games101_hw4", WIDTH, HEIGHT, color_buffer);
}
