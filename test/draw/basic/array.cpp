#include "gpu_execuator.hpp"
#include "gpu_execuator_with_vram.hpp"
#include "common/utils.hpp"

TEST_F(GPUExecuator_with_vram, array_add_with_vram) {
    uint32_t count = 16;
    int i = 0;

    // Data
    uint64_t in = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(int));
    for (i=0; i<count; i++) {
        gpu_write_vram(in + i * sizeof(int), i * 100, sizeof(int));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "array_add");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(3 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in);
    PushParam_with_vram(params_addr, 2, (uint64_t)out);

    run1d_with_vram(count, params_addr, 3);

    for (i=0; i<count; i++) {
        int expected = (i * 100) + 100;
        int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
        EXPECT_EQ(result, expected);
    }
}

TEST_F(GPUExecuator, array_add) {
    int32_t count = 16;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("basic", "array_add");
    // long gpumain(long tid, int *input, int* output)
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}

TEST_F(GPUExecuator_with_vram, multi_array_add_with_vram) {
    uint32_t count = 32;
    int i = 0;

    // Data
    uint64_t in1 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t in2 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(int));
    for (i=0; i<count; i++) {
        gpu_write_vram(in1 + i * sizeof(int), i * 100, sizeof(int));
        gpu_write_vram(in2 + i * sizeof(int), i + 34, sizeof(int));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "multi_array_add");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(4 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in1);
    PushParam_with_vram(params_addr, 2, (uint64_t)in2);
    PushParam_with_vram(params_addr, 3, (uint64_t)out);

    run1d_with_vram(count, params_addr, 4);

    for (i=0; i<count; i++) {
        int expected = (i * 100) + (i + 34);
        int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
        EXPECT_EQ(result, expected);
    }
}

TEST_F(GPUExecuator, multi_array_add) {
    int32_t count = 32;
    int32_t i = 0;
    uint32_t *in1 = (uint32_t *)malloc(count * 4);
    uint32_t *in2 = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    LoadELF("basic", "multi_array_add");
    // long vs_main(long tid, int *input1, int *input2, int *output)
    PushParam(0);
    PushParam((uint64_t)in1);
    PushParam((uint64_t)in2);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        out[i] = 5678;   // test of array[i] + array[i];
    }

    run1d(count);

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] + in2[i]);
    }
}

TEST_F(GPUExecuator_with_vram, multi_array_mul_with_vram) {
    uint32_t count = 32;
    int i = 0;

    // Data
    uint64_t in1 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t in2 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(int));
    for (i=0; i<count; i++) {
        gpu_write_vram(in1 + i * sizeof(int), i * 100, sizeof(int));
        gpu_write_vram(in2 + i * sizeof(int), i + 34, sizeof(int));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "multi_array_mul");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(4 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in1);
    PushParam_with_vram(params_addr, 2, (uint64_t)in2);
    PushParam_with_vram(params_addr, 3, (uint64_t)out);

    run1d_with_vram(count, params_addr, 4);

    for (i=0; i<count; i++) {
        int expected = (i * 100) * (i + 34);
        int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
        EXPECT_EQ(result, expected);
    }
}

TEST_F(GPUExecuator, multi_array_mul) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in1 = (uint32_t *)malloc(count * 4);
    uint32_t *in2 = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    LoadELF("basic", "multi_array_mul");
    // long gpumain(long tid, int *input1, int *input2, int *output)
    PushParam(0);
    PushParam((uint64_t)in1);
    PushParam((uint64_t)in2);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        out[i] = 5678;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] * in2[i]);
    }
}

TEST_F(GPUExecuator_with_vram, multi_array_muladd_with_vram) {
    uint32_t count = 32;
    int i = 0;

    // Data
    uint64_t in1 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t in2 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t in3 = (uint64_t) gpu_malloc(count * sizeof(int));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(int));
    for (i=0; i<count; i++) {
        gpu_write_vram(in1 + i * sizeof(int), i * 100, sizeof(int));
        gpu_write_vram(in2 + i * sizeof(int), i + 34, sizeof(int));
        gpu_write_vram(in3 + i * sizeof(int), i * 4, sizeof(int));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "multi_array_muladd");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(5 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in1);
    PushParam_with_vram(params_addr, 2, (uint64_t)in2);
    PushParam_with_vram(params_addr, 3, (uint64_t)in3);
    PushParam_with_vram(params_addr, 4, (uint64_t)out);

    run1d_with_vram(count, params_addr, 5);

    for (i=0; i<count; i++) {
        int expected = (i * 100) * (i + 34) + (i * 4);
        int result = gpu_read_vram(out + i * sizeof(int), sizeof(int));
        EXPECT_EQ(result, expected);
    }
}

TEST_F(GPUExecuator, multi_array_muladd) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in1 = (uint32_t *)malloc(count * 4);
    uint32_t *in2 = (uint32_t *)malloc(count * 4);
    uint32_t *in3 = (uint32_t *)malloc(count * 4);
    uint32_t *out = (uint32_t *)malloc(count * 4);

    LoadELF("basic", "multi_array_muladd");
    // long gpumain(long tid, int *input1, int *input2, int *output)
    PushParam(0);
    PushParam((uint64_t)in1);
    PushParam((uint64_t)in2);
    PushParam((uint64_t)in3);
    PushParam((uint64_t)out);


    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        in3[i] = i * 4;
        out[i] = 5678;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] * in2[i] + in3[i]);
    }
}

TEST_F(GPUExecuator_with_vram, multi_array_fmuladd_with_vram) {
    uint32_t count = 32;
    int i = 0;

    // Data
    uint64_t in1 = (uint64_t) gpu_malloc(count * sizeof(uint32_t));
    uint64_t in2 = (uint64_t) gpu_malloc(count * sizeof(uint32_t));
    uint64_t in3 = (uint64_t) gpu_malloc(count * sizeof(uint32_t));
    uint64_t out = (uint64_t) gpu_malloc(count * sizeof(uint32_t));
    for (i=0; i<count; i++) {
        gpu_write_vram(in1 + i * sizeof(uint32_t), utils::f2ui(i * 100.0f), sizeof(uint32_t));
        gpu_write_vram(in2 + i * sizeof(uint32_t), utils::f2ui(i + 34.0f), sizeof(uint32_t));
        gpu_write_vram(in3 + i * sizeof(uint32_t), utils::f2ui(i * 4.0f), sizeof(uint32_t));
    }

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "multi_array_fmuladd");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(5 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)in1);
    PushParam_with_vram(params_addr, 2, (uint64_t)in2);
    PushParam_with_vram(params_addr, 3, (uint64_t)in3);
    PushParam_with_vram(params_addr, 4, (uint64_t)out);

    run1d_with_vram(count, params_addr, 5);

    for (i=0; i<count; i++) {
        float expected = (i * 100.0f) * (i + 34.0f) + (i * 4.0f);
        uint32_t result = gpu_read_vram(out + i * sizeof(uint32_t), sizeof(uint32_t));
        EXPECT_EQ(utils::ui2f(result), expected);
    }
}

TEST_F(GPUExecuator, multi_array_fmuladd) {
    int32_t count = 32;
    int i = 0;
    float *in1 = (float *)malloc(count * 4);
    float *in2 = (float *)malloc(count * 4);
    float *in3 = (float *)malloc(count * 4);
    float *out = (float *)malloc(count * 4);

    LoadELF("basic", "multi_array_fmuladd");
    // long gpumain(long tid, int *input1, int *input2, int *output)
    PushParam(0);
    PushParam((uint64_t)in1);
    PushParam((uint64_t)in2);
    PushParam((uint64_t)in3);
    PushParam((uint64_t)out);


    for (i=0; i<count; i++) {
        in1[i] = i * 100;
        in2[i] = i + 34;
        in3[i] = i * 4;
        out[i] = 5678;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        EXPECT_EQ(out[i], in1[i] * in2[i] + in3[i]);
    }
}