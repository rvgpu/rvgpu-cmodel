#include <gtest/gtest.h>

#include "top/rvgpu.h"

#include "draw.hpp"

TEST_F(Draw, branch_if) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    shader.SetupShaderBinary("branch_if.vs");
    shader.SetupIO(0, (uint64_t)in);
    shader.SetupIO(1, (uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            EXPECT_EQ(out[i], in[i] + 100);
        } else {
            EXPECT_EQ(out[i], in[i]);
        }
    }
}

TEST_F(Draw, branch_ifelse) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    shader.SetupShaderBinary("branch_ifelse.vs");
    shader.SetupIO(0, (uint64_t)in);
    shader.SetupIO(1, (uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            EXPECT_EQ(out[i], in[i] + 100);
        } else {
            EXPECT_EQ(out[i], in[i] + 200);
        }
    }
}

TEST_F(Draw, branch_ifif) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    shader.SetupShaderBinary("branch_ifif.vs");
    shader.SetupIO(0, (uint64_t)in);
    shader.SetupIO(1, (uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            if (i%4 == 0) {
                EXPECT_EQ(out[i], in[i] + 400);
            } else {
                EXPECT_EQ(out[i], in[i] + 200);
            }
        } else {
            EXPECT_EQ(out[i], in[i] + 100);
        }
    }
}

TEST_F(Draw, branch_for) {
    Shader shader;
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    shader.SetupShaderBinary("branch_for.vs");
    shader.SetupIO(0, (uint64_t)in);
    shader.SetupIO(1, (uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)shader.layout);
    end_command();

    run();

    for (i=0; i<count; i++) {
        uint32_t expect_out = in[i];
        for (int j=0; j<i; j++) {
            expect_out += j;
        }

        EXPECT_EQ(out[i], expect_out);
    }
}