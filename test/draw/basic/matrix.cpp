#include "gpu_execuator.hpp"
#include "gpu_execuator_with_vram.hpp"
#include "common/utils.hpp"

#include "data/matrix_model.hpp"

#include <eigen3/Eigen/Eigen>

TEST_F(GPUExecuator_with_vram, matrix_model_with_vram) {
    int i = 0;

    // Data
    uint64_t out = (uint64_t) gpu_malloc(16 * sizeof(uint32_t));

    // Shader
    uint64_t shader_addr = (uint64_t) gpu_malloc(0x2000000 * sizeof(uint32_t));
    LoadELF_with_vram(shader_addr, "basic", "matrix_model");

    // Parameters
    uint64_t params_addr = (uint64_t) gpu_malloc(2 * sizeof(uint64_t));
    PushParam_with_vram(params_addr, 0, 0);
    PushParam_with_vram(params_addr, 1, (uint64_t)out);

    run1d_with_vram(1, params_addr, 2);

    float *expected = (float *)malloc(16 * sizeof(float));
    gpumain(0, expected);

    for (i=0; i<16; i++) {
        uint32_t result = gpu_read_vram(out + i * sizeof(uint32_t), sizeof(uint32_t));
        EXPECT_FLOAT_EQ(utils::ui2f(result), expected[i]);
    }
}

TEST_F(GPUExecuator, matrix_model) {
    float *data = (float *)malloc(sizeof(float) * 16);
    float *result = (float *)malloc(sizeof(float) * 16);

    LoadELF("basic", "matrix_model");
    PushParam(0); // tid
    PushParam((uint64_t)data);
    run1d(1);

    gpumain(0, result);

    for (uint32_t i=0; i<16; i++) {
        EXPECT_FLOAT_EQ(data[i], result[i]);
    }
}