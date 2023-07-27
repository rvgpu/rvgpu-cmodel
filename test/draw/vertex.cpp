#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "common/command_stream.h"

#include "draw.hpp"

TEST_F(Draw, vertex_shader_add) {
    int i = 0;
    uint32_t binary[SHADER_BINARY_SIZE];
    load_shader("add.vs", binary);

    struct addlayout {
        uint64_t input;
        uint64_t output;
    };
    struct addlayout *layout = (struct addlayout *)malloc(sizeof(struct addlayout));
    layout->input = (uint64_t)malloc(100);
    layout->output = (uint64_t)malloc(100);
    command_stream_vs cs_vs = {};
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
