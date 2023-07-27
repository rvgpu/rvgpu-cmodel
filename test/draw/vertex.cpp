#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "common/command_stream.h"

#include "draw.hpp"

TEST_F(Draw, vertex_shader_array_add) {
    int i = 0;
    uint32_t binary[SHADER_BINARY_SIZE];
    load_shader("array_add.vs", binary);

    struct addlayout {
        uint64_t input;
        uint64_t output;
    };
    struct addlayout *layout = (struct addlayout *)malloc(sizeof(struct addlayout));
    layout->input = (uint64_t)malloc(100);
    layout->output = (uint64_t)malloc(100);
    rvgpu_command_vs cs_vs = {};
    cs_vs.vertex_count = 16;
    cs_vs.layout = (uint64_t)layout;
    cs_vs.shader = (uint64_t)binary;

    vertex_command(cs_vs);
    end_command();

    // input of data
    int *in = (int *)layout->input;
    for (i=0; i<16; i++) {
        in[i] = i * 100;
    }

    run();

    int *out = (int *)layout->output;
    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}

TEST_F(Draw, vertex_shader_multi_array_add) {
    int i = 0;
    uint32_t binary[SHADER_BINARY_SIZE];
    load_shader("multi_array_add.vs", binary);

    struct addlayout {
        uint64_t input1;
        uint64_t input2;
        uint64_t output;
    };
    struct addlayout *layout = (struct addlayout *)malloc(sizeof(struct addlayout));
    layout->input1 = (uint64_t)malloc(100);
    layout->input2 = (uint64_t)malloc(100);
    layout->output = (uint64_t)malloc(100);
    rvgpu_command_vs cs_vs = {};
    cs_vs.vertex_count = 32;
    cs_vs.layout = (uint64_t)layout;
    cs_vs.shader = (uint64_t)binary;

    vertex_command(cs_vs);
    end_command();

    // input of data
    int *in1 = (int *)layout->input1;
    int *in2 = (int *)layout->input2;
    for (i=0; i<32; i++) {
        in1[i] = i * 100;
        in2[i] = i * 23;
    }

    run();

    int *out = (int *)layout->output;
    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in1[i] + in2[i]);
    }
}
