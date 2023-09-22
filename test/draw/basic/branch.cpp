#include "gpu_execuator.hpp"
#include "gpu_execuator_with_vram.hpp"

TEST_F(GPUExecuator_with_vram, branch_if_with_vram) {
    uint32_t count = 32;
    int i = 0;

    // Data
    uint64_t in = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(int));
    for (i=0; i<count; i++) {
        gpu_write_vram(in + i * sizeof(int), i * 100, sizeof(int));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "branch_if");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(3 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in);
    PushParam_with_vram(params_addr, 2, (uint64_t)out);

    run1d_with_vram(count, params_addr, 3);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
            EXPECT_EQ(result, (i * 100) + 100);
        } else {
            int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
            EXPECT_EQ(result, (i * 100));
        }
    }
}

TEST_F(GPUExecuator, branch_if) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("basic", "branch_if");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            EXPECT_EQ(out[i], in[i] + 100);
        } else {
            EXPECT_EQ(out[i], in[i]);
        }
    }
}

TEST_F(GPUExecuator_with_vram, branch_ifelse_with_vram) {
    uint32_t count = 32;
    int i = 0;

    // Data
    uint64_t in = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(int));
    for (i=0; i<count; i++) {
        gpu_write_vram(in + i * sizeof(int), i * 100, sizeof(int));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "branch_ifelse");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(3 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in);
    PushParam_with_vram(params_addr, 2, (uint64_t)out);

    run1d_with_vram(count, params_addr, 3);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
            EXPECT_EQ(result, (i * 100) + 100);
        } else {
            int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
            EXPECT_EQ(result, (i * 100) + 200);
        }
    }
}

TEST_F(GPUExecuator, branch_ifelse) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("basic", "branch_ifelse");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            EXPECT_EQ(out[i], in[i] + 100);
        } else {
            EXPECT_EQ(out[i], in[i] + 200);
        }
    }
}

TEST_F(GPUExecuator, branch_ifif) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("basic", "branch_ifif");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

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

TEST_F(GPUExecuator, branch_for) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("basic", "branch_for");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        uint32_t expect_out = in[i];
        for (int j=0; j<i; j++) {
            expect_out += j;
        }

        EXPECT_EQ(out[i], expect_out);
    }
}