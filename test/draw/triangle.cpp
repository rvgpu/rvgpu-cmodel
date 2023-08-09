#include "gpu_execuator.hpp"

#include "data/vertex_shader_vt14.c"
#include "data/fragment_shader_vt14.c"

TEST_F(GPUExecuator, triangle) {
    int32_t count = 3;

    struct viewport *vp = (struct viewport *) malloc(sizeof(struct viewport));
    vp->x = 0.0f;
    vp->y = 0.0f;
    vp->w = 400.0f;
    vp->h = 300.0f;

    float *vsout_position = (float *) malloc(count * 12 * sizeof(float));
    float *vsout_color = (float *) malloc(count * 12 * sizeof(float));

    LoadELF("vertex_shader_vt14");
    PushParam(0); // vid
    PushParam((uint64_t)vsout_position);
    PushParam((uint64_t)vsout_color);
    PushParam((uint64_t)vp);
    run1d(count);

    printf("FRAGMENT SHADER\n");
    LoadELF("fragment_shader_vt14");
    char *fb = (char *)malloc(800 * 600 * 4);
    char *testfb = (char *)malloc(800 * 600 * 4);
    // long gpumain(long pixel, float *in_position, float *in_color, float *out_color_buffer, int v0_id, int v1_id, int v2_id)
    PushParam(0);
    PushParam((uint64_t)vsout_position);
    PushParam((uint64_t)vsout_color);
    PushParam((uint64_t)fb);
    PushParam(0); // v0_id
    PushParam(1); // v1_id
    PushParam(2); // v2_id
    // run1d(800 * 600);


    for (uint32_t i=0; i<800*600; i++) {
        uint32_t index = i;
        gpumain(index, vsout_position, vsout_color, testfb, 0, 1, 2);
        // EXPECT_EQ(testfb[index * 4 + 0], fb[index * 4 + 0]);// EXPECT_EQ(testfb[index * 4 + 1], fb[index * 4 + 1]);
        // EXPECT_EQ(testfb[index * 4 + 2], fb[index * 4 + 2]);
        // EXPECT_EQ(testfb[index * 4 + 3], fb[index * 4 + 3]);
    }

    WritePPM("triangle", 800, 600, testfb);
}
