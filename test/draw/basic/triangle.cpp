#include "gpu_execuator.hpp"
#include "gpu_execuator_with_vram.hpp"
#include "common/utils.hpp"

#include "data/vertex_shader_vt14.h"
#include "data/fragment_shader_vt14.h"

TEST_F(GPUExecuator_with_vram, triangle_with_vram) {
    uint32_t count = 3;

    struct viewport *vp_host = (struct viewport *) malloc(sizeof(struct viewport));
    vp_host->x = 0.0f;
    vp_host->y = 0.0f;
    vp_host->w = 400.0f;
    vp_host->h = 300.0f;

    // Vertex shader data
    uint64_t vsout_position = (uint64_t) gpu_malloc(count * 4 * sizeof(uint32_t));
    uint64_t vsout_color = (uint64_t) gpu_malloc(count * 3 * sizeof(uint32_t));
    uint64_t vp = (uint64_t) gpu_malloc(sizeof(struct viewport));
    gpu_memcpy(vp, (uint64_t)vp_host, sizeof(struct viewport), true);

    // Vertex shader
    uint64_t vertex_shader_addr = (uint64_t) gpu_malloc(0x1000000 * sizeof(uint32_t));
    LoadELF_with_vram(vertex_shader_addr, "basic", "vertex_shader_vt14");

    // Vertex shader parameters
    uint64_t vs_params_addr = (uint64_t) gpu_malloc(4 * sizeof(uint64_t));
    PushParam_with_vram(vs_params_addr, 0, 0);
    PushParam_with_vram(vs_params_addr, 1, (uint64_t)vsout_position);
    PushParam_with_vram(vs_params_addr, 2, (uint64_t)vsout_color);
    PushParam_with_vram(vs_params_addr, 3, (uint64_t)vp);

    run1d_with_vram(count, vs_params_addr, 4);

    // Fragment shader data
    uint64_t fb = (uint64_t) gpu_malloc(800 * 600 * 4);

    // Fragment shader
    uint64_t fragment_shader_addr = (uint64_t) gpu_malloc(0x1000000 * sizeof(uint32_t));
    LoadELF_with_vram(fragment_shader_addr, "basic", "fragment_shader_vt14");

    // Fragment shader parameters
    uint64_t fs_params_addr = (uint64_t) gpu_malloc(7 * sizeof(uint64_t));
    PushParam_with_vram(fs_params_addr, 0, 0);
    PushParam_with_vram(fs_params_addr, 1, (uint64_t)vsout_position);
    PushParam_with_vram(fs_params_addr, 2, (uint64_t)vsout_color);
    PushParam_with_vram(fs_params_addr, 3, (uint64_t)fb);
    PushParam_with_vram(fs_params_addr, 4, 0);
    PushParam_with_vram(fs_params_addr, 5, 1);
    PushParam_with_vram(fs_params_addr, 6, 2);

    run1d_with_vram(800 * 600, fs_params_addr, 7);

    // Check result
    float *myposition = (float *) malloc(count * 4 * sizeof(float));
    float *mycolor = (float *) malloc(count * 3 * sizeof(float));
    unsigned char *testfb = (unsigned char *) calloc(800 * 600 * 4, 1);

    for (uint32_t i=0; i<count; i++) {
        vertex_shader(i, myposition, mycolor, vp_host);
    }

    for (uint32_t i=0; i<800*600; i++) {
        fragment_shader(i, myposition, mycolor, testfb, 0, 1, 2);

        unsigned char result_r = gpu_read_vram(fb + i * 4 + 0, 1);
        unsigned char result_g = gpu_read_vram(fb + i * 4 + 1, 1);
        unsigned char result_b = gpu_read_vram(fb + i * 4 + 2, 1);
        unsigned char result_a = gpu_read_vram(fb + i * 4 + 3, 1);

        EXPECT_EQ(testfb[i * 4 + 0], result_r);
        EXPECT_EQ(testfb[i * 4 + 1], result_g);
        EXPECT_EQ(testfb[i * 4 + 2], result_b);
        EXPECT_EQ(testfb[i * 4 + 3], result_a);
    }

    WritePPM("triangle_with_vram", 800, 600, testfb);
}

TEST_F(GPUExecuator, triangle) {
    int32_t count = 3;

    struct viewport *vp = (struct viewport *) malloc(sizeof(struct viewport));
    vp->x = 0.0f;
    vp->y = 0.0f;
    vp->w = 400.0f;
    vp->h = 300.0f;

    float *vsout_position = (float *) malloc(count * 4 * sizeof(float));
    float *vsout_color = (float *) malloc(count * 3 * sizeof(float));

    LoadELF("basic", "vertex_shader_vt14");
    PushParam(0); // vid
    PushParam((uint64_t)vsout_position);
    PushParam((uint64_t)vsout_color);
    PushParam((uint64_t)vp);
    run1d(count);

    LoadELF("basic", "fragment_shader_vt14");
    unsigned char *fb = (unsigned char *)malloc(800 * 600 * 4);
    unsigned char *testfb = (unsigned char *)malloc(800 * 600 * 4);
    // long gpumain(long pixel, float *in_position, float *in_color, float *out_color_buffer, int v0_id, int v1_id, int v2_id)
    PushParam(0);
    PushParam((uint64_t)vsout_position);
    PushParam((uint64_t)vsout_color);
    PushParam((uint64_t)fb);
    PushParam(0); // v0_id
    PushParam(1); // v1_id
    PushParam(2); // v2_id
    run1d(800 * 600);


    for (uint32_t i=0; i<800*600; i++) {
        uint32_t index = i;
        fragment_shader(index, vsout_position, vsout_color, testfb, 0, 1, 2);
        EXPECT_EQ(testfb[index * 4 + 0], fb[index * 4 + 0]);
        EXPECT_EQ(testfb[index * 4 + 1], fb[index * 4 + 1]);
        EXPECT_EQ(testfb[index * 4 + 2], fb[index * 4 + 2]);
        EXPECT_EQ(testfb[index * 4 + 3], fb[index * 4 + 3]);
    }

    WritePPM("triangle", 800, 600, fb);
}
