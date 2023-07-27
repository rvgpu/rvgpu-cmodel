#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "cp/command_stream.h"

TEST(Draw, Draw_add) {
    #include "add.vs"

    rvgpu rvgpu;

    cs_vs_desc *vs = (cs_vs_desc *)malloc(sizeof(cs_vs_desc));
    vs->input = (uint64_t)malloc(100);
    vs->output = (uint64_t)malloc(100);
    vs->shader = (uint64_t)add_vs;
    int *in = (int *)vs->input;
    for (int i=0; i<16; i++) {
        in[i] = i * 100;
    }

    std::vector<command_stream> cs;
    command_stream_vs cs_vs;
    cs_vs.vertex_count = 16;
    cs_vs.desc = (uint64_t)vs;


    cs.push_back(command_stream {.type = CS_TYPE_VS, .cmd = {cs_vs}});
    cs.push_back(command_stream {.type = CS_TYPE_END, .cmd = {}});

    rvgpu.run((uint64_t)cs.data());

    EXPECT_STRNE("Hello", "gtest");
}
