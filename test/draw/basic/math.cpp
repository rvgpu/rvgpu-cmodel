#include "gpu_execuator.hpp"

#include "data/math.hpp"
TEST_F(GPUExecuator, test_math_function) {
    int count = 16;
    float *in1 = (float *)malloc(sizeof(float) * count);
    float *in2 = (float *)malloc(sizeof(float) * count);
    float *out = (float *)malloc(sizeof(float) * count);
    float *ref = (float *)malloc(sizeof(float) * count);

    // out[0] = cos(in1[0]);
    in1[0] = 30.0f;
    // out[1] = sin(in1[1]);
    in1[1] = 30.0f;
    // out[2] = pow(in1[2], in2[2])
    in1[2] = 3.0f;
    in2[2] = 4.0f;

    LoadELF("basic", "math");
    // void testmath(long tid, float *in1, float *in2, float *out) {
    PushParam(0); // tid
    PushParam((uint64_t)in1);
    PushParam((uint64_t)in2);
    PushParam((uint64_t)out);
    // run1d(1);

    testmath(0, in1, in2, ref);

    for (uint32_t i=0; i<16; i++) {
        // EXPECT_FLOAT_EQ(out[i], ref[i]);
    }
}