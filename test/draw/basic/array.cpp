#include "gpu_execuator.hpp"

TEST_F(GPUExecuator, float_times_int) {
    int32_t count = 16;
    int i = 0;
    uint32_t *in_int = (uint32_t *)malloc(count * sizeof(uint32_t));
    float *in_float = (float *)malloc(count * sizeof(float));

    int *out = (int *)malloc(count * sizeof(int));

    LoadELF("basic", "float_times_int");
    // long gpumain(long tid, int *in_int, float *in_float, int* output)
    PushParam(0);
    PushParam((uint64_t)in_int);
    PushParam((uint64_t)in_float);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in_int[i] = i;
        in_float[i] = 1.3;

        // int test = in_int[i] * (-1.3);
        // printf("test: %d\n", test);
    }

    run1d(count);

    for (i=0; i<16; i++) {
        printf("%d\n", out[i]);
        // std::cout<<out[i]<<" --> out[i]\n";

        // EXPECT_EQ(out[i], in[i] + 100);
    }
}

TEST_F(GPUExecuator, vertex_shader_array_add) {
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

    for (i=0; i<16; i++) {
        EXPECT_EQ(out[i], in[i] + 100);
    }
}

TEST_F(GPUExecuator, vertex_shader_multi_array_add) {
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

TEST_F(GPUExecuator, vertex_shader_multi_array_mul) {
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

TEST_F(GPUExecuator, vertex_shader_multi_array_muladd) {
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

TEST_F(GPUExecuator, vertex_shader_multi_array_fmuladd) {
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