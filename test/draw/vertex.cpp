#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "common/command_stream.h"

#include "draw.hpp"

TEST_F(Draw, vertex_shader_array_add) {
    Shader shader;
    int32_t count = 16;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    shader.SetupShaderBinary("array_add.vs");
    shader.SetupIO(0, (uint64_t)in);
    shader.SetupIO(1, (uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}

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
