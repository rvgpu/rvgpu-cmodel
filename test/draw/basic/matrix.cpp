#include "gpu_execuator.hpp"
#include "data/matrix_model.hpp"

#include <eigen3/Eigen/Eigen>

TEST_F(GPUExecuator, vertex_shader_vt14) {
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