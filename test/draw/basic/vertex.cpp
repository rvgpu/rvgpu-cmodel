#include "gpu_execuator.hpp"
#include "gpu_execuator_with_vram.hpp"
#include "common/utils.hpp"

#include "data/vertex_shader_vt14.h"

TEST_F(GPUExecuator_with_vram, vertex_shader_vt14_with_vram) {
    uint32_t count = 3;

    struct viewport *vp_host = (struct viewport *) malloc(sizeof(struct viewport));
    vp_host->x = 0.0f;
    vp_host->y = 0.0f;
    vp_host->w = 400.0f;
    vp_host->h = 300.0f;

    // Data
    uint64_t out_position = (uint64_t) gpu_malloc(count * 4 * sizeof(uint32_t));
    uint64_t out_color = (uint64_t) gpu_malloc(count * 3 * sizeof(uint32_t));
    uint64_t vp = (uint64_t) gpu_malloc(sizeof(struct viewport));
    gpu_memcpy(vp, (uint64_t)vp_host, sizeof(struct viewport), true);

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "vertex_shader_vt14");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(4 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)out_position);
    PushParam_with_vram(params_addr, 2, (uint64_t)out_color);
    PushParam_with_vram(params_addr, 3, (uint64_t)vp);

    run1d_with_vram(count, params_addr, 4);

    float *myposition = (float *) malloc(count * 4 * sizeof(float));
    float *mycolor = (float *) malloc(count * 3 * sizeof(float));

    for (uint32_t i=0; i<count; i++) {
        gpumain(i, myposition, mycolor, vp_host);

        uint32_t result_x = gpu_read_vram(out_position + (i * 4 + 0) * sizeof(uint32_t), sizeof(uint32_t));
        uint32_t result_y = gpu_read_vram(out_position + (i * 4 + 1) * sizeof(uint32_t), sizeof(uint32_t));
        uint32_t result_z = gpu_read_vram(out_position + (i * 4 + 2) * sizeof(uint32_t), sizeof(uint32_t));
        uint32_t result_w = gpu_read_vram(out_position + (i * 4 + 3) * sizeof(uint32_t), sizeof(uint32_t));

        uint32_t result_r = gpu_read_vram(out_color + (i * 3 + 0) * sizeof(uint32_t), sizeof(uint32_t));
        uint32_t result_g = gpu_read_vram(out_color + (i * 3 + 1) * sizeof(uint32_t), sizeof(uint32_t));
        uint32_t result_b = gpu_read_vram(out_color + (i * 3 + 2) * sizeof(uint32_t), sizeof(uint32_t));

        EXPECT_EQ(utils::ui2f(result_x), myposition[i * 4 + 0]);
        EXPECT_EQ(utils::ui2f(result_y), myposition[i * 4 + 1]);
        EXPECT_EQ(utils::ui2f(result_z), myposition[i * 4 + 2]);
        EXPECT_EQ(utils::ui2f(result_w), myposition[i * 4 + 3]);

        EXPECT_EQ(utils::ui2f(result_r), mycolor[i * 3 + 0]);
        EXPECT_EQ(utils::ui2f(result_g), mycolor[i * 3 + 1]);
        EXPECT_EQ(utils::ui2f(result_b), mycolor[i * 3 + 2]);
    }
}

TEST_F(GPUExecuator, vertex_shader_vt14) {
    int32_t count = 3;

    struct viewport *vp = (struct viewport *) malloc(sizeof(struct viewport));
    vp->x = 0.0f;
    vp->y = 0.0f;
    vp->w = 400.0f;
    vp->h = 300.0f;

    float *out_position = (float *) malloc(count * 4 * sizeof(float));
    float *out_color = (float *) malloc(count * 3 * sizeof(float));

    LoadELF("basic", "vertex_shader_vt14");
    PushParam(0); // vid
    PushParam((uint64_t)out_position);
    PushParam((uint64_t)out_color);
    PushParam((uint64_t)vp);
    run1d(count);

    float *myposition = (float *) malloc(count * 4 * sizeof(float));
    float *mycolor = (float *) malloc(count * 3 * sizeof(float));
    for (int32_t i=0; i<count; i++) {
        gpumain(i, myposition, mycolor, vp);

        EXPECT_EQ(out_position[i * 4 + 0], myposition[i * 4 + 0]);
        EXPECT_EQ(out_position[i * 4 + 1], myposition[i * 4 + 1]);
        EXPECT_EQ(out_position[i * 4 + 2], myposition[i * 4 + 2]);
        EXPECT_EQ(out_position[i * 4 + 3], myposition[i * 4 + 3]);

        EXPECT_EQ(out_color[i * 3 + 0], mycolor[i * 3 + 0]);
        EXPECT_EQ(out_color[i * 3 + 1], mycolor[i * 3 + 1]);
        EXPECT_EQ(out_color[i * 3 + 2], mycolor[i * 3 + 2]);
    }
}