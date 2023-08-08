#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "common/command_stream.h"

#include "gpu_execuator.hpp"

TEST_F(GPUExecuator, vertex_shader_array_add) {
    int32_t count = 16;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("array_add");
    // long gpumain(long tid, int *input, int* output)
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(0, 16);

    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}

#if 0
TEST_F(Draw, vertex_shader_multi_array_add) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in1 = (uint32_t *)malloc(count * 4);
    uint32_t *in2 = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    shader.SetupShaderBinary("multi_array_add.vs");
    shader.SetupIO(0, (uint64_t)in1);
    shader.SetupIO(1, (uint64_t)in2);
    shader.SetupIO(2, (uint64_t)out);

    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        out[i] = 5678;   // test of array[i] + array[i];
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] + in2[i]);
    }
}

TEST_F(Draw, vertex_shader_multi_array_mul) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in1 = (uint32_t *)malloc(count * 4);
    uint32_t *in2 = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    shader.SetupShaderBinary("multi_array_mul.vs");
    shader.SetupIO(0, (uint64_t)in1);
    shader.SetupIO(1, (uint64_t)in2);
    shader.SetupIO(2, (uint64_t)out);

    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        out[i] = 5678;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] * in2[i]);
    }
}

TEST_F(Draw, vertex_shader_multi_array_muladd) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in1 = (uint32_t *)malloc(count * 4);
    uint32_t *in2 = (uint32_t *)malloc(count * 4);
    uint32_t *in3 = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    shader.SetupShaderBinary("multi_array_muladd.vs");
    shader.SetupIO(0, (uint64_t)in1);
    shader.SetupIO(1, (uint64_t)in2);
    shader.SetupIO(2, (uint64_t)in3);
    shader.SetupIO(3, (uint64_t)out);

    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        in3[i] = i * 4;
        out[i] = 5678;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] * in2[i] + in3[i]);
    }
}

TEST_F(Draw, vertex_shader_vt14) {
    Shader shader;
    int32_t count = 3;    

    struct viewport {
        float x;
        float y;
        float w;
        float h;
    };

    typedef struct {
        unsigned long vp;
        unsigned long out_position;
        unsigned long out_color;
    } io;

    struct viewport *my_vp = (struct viewport *) malloc(sizeof(struct viewport));
    my_vp->x = 0.0f;
    my_vp->y = 0.0f;
    my_vp->w = 400.0f;
    my_vp->h = 300.0f;

    float *my_position = (float *) malloc(count * 7 * sizeof(float));
    float *my_color = (float *) malloc(count * 7 * sizeof(float));

    io *my_io = (io *) malloc(sizeof(io));

    my_io->vp = reinterpret_cast<unsigned long>(my_vp);
    my_io->out_position = reinterpret_cast<unsigned long>(my_position);
    my_io->out_color = reinterpret_cast<unsigned long>(my_color);

    shader.SetupShaderBinary("vertex_shader_vt14.vs");

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)my_io);

    end_command();

    run();

    // Test
    float position[3][2] = {
        {-0.5, 0.5},
        {0.5, 0.5},
        {0, -0.5}
    };

    float colors[3][3] = {
        {0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
    };

    float fx, fy, fz, fw, fr, fg, fb;
    int i;

    for (i = 0; i < count; i++) {
        fx = position[i][0];
        fy = position[i][1];
        fz = 0.0f;
        fw = 1.0f;
        fr = colors[i][0];
        fg = colors[i][1];
        fb = colors[i][2];

        fx = my_vp->w + fx * (my_vp->w);
        fy = my_vp->h + fy * (my_vp->h);

        float *gl_Position = reinterpret_cast<float *>(my_io->out_position);
        float *fragColor = reinterpret_cast<float *>(my_io->out_color);

        EXPECT_EQ(gl_Position[i * 7 + 0], fx);
        EXPECT_EQ(gl_Position[i * 7 + 1], fy);
        EXPECT_EQ(gl_Position[i * 7 + 2], fz);
        EXPECT_EQ(gl_Position[i * 7 + 3], fw);

        EXPECT_EQ(fragColor[i * 7 + 4], fr);
        EXPECT_EQ(fragColor[i * 7 + 5], fg);
        EXPECT_EQ(fragColor[i * 7 + 6], fb);
    }
}
#endif