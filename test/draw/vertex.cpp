#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "cp/command_stream.h"
#include "read_asm.hpp"

TEST(Draw, Draw_add) {
    uint32_t binary[1000];
    read_asm_file("add.vs", binary);

    rvgpu rvgpu;

    cs_vs_desc *vs = (cs_vs_desc *)malloc(sizeof(cs_vs_desc));
    vs->input = (uint64_t)malloc(100);
    vs->output = (uint64_t)malloc(100);
    vs->shader = (uint64_t)binary;
    int *in = (int *)vs->input;
    int i = 0;
    for (i=0; i<16; i++) {
        in[i] = i * 100;
    }

    std::vector<command_stream> cs;
    command_stream_vs cs_vs;
    cs_vs.vertex_count = 16;
    cs_vs.desc = (uint64_t)vs;


    cs.push_back(command_stream {.type = CS_TYPE_VS, .cmd = {cs_vs}});
    cs.push_back(command_stream {.type = CS_TYPE_END, .cmd = {}});

    rvgpu.run((uint64_t)cs.data());

    int *out = (int *)vs->output;
    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}
