#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "common/command_stream.h"

#include "draw.hpp"

TEST_F(Draw, vertex_shader_add) {
    int i = 0;
    uint32_t binary[SHADER_BINARY_SIZE];

    load_shader("add.vs", binary);
    cs_vs_desc *vs = (cs_vs_desc *)malloc(sizeof(cs_vs_desc));
    vs->input = (uint64_t)malloc(100);
    vs->output = (uint64_t)malloc(100);
    vs->shader = (uint64_t)binary;
    command_stream_vs cs_vs = {};
    cs_vs.vertex_count = 16;
    cs_vs.desc = (uint64_t)vs;

    vertex_command(cs_vs);
    end_command();

    // input of data
    int *in = (int *)vs->input;
    for (i=0; i<16; i++) {
        in[i] = i * 100;
    }

    run();

    int *out = (int *)vs->output;
    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}
