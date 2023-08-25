#include "gpu_execuator.hpp"

#include "data/vertex_shader_vt14.h"

TEST_F(GPUExecuator, vertex_shader_vt14) {
    int32_t count = 3;

    struct viewport *vp = (struct viewport *) malloc(sizeof(struct viewport));
    vp->x = 0.0f;
    vp->y = 0.0f;
    vp->w = 400.0f;
    vp->h = 300.0f;

    float *out_position = (float *) malloc(count * 12 * sizeof(float));
    float *out_color = (float *) malloc(count * 12 * sizeof(float));

    LoadELF("basic", "vertex_shader_vt14");
    PushParam(0); // vid
    PushParam((uint64_t)out_position);
    PushParam((uint64_t)out_color);
    PushParam((uint64_t)vp);
    run1d(count);

    float *myposition = (float *) malloc(count * 12 * sizeof(float));
    float *mycolor = (float *) malloc(count * 12 * sizeof(float));
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