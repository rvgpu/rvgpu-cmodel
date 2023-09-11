#include "ut_inst.hpp"
#include <math.h>

TEST_F(ut_inst, decode_and_execute_rv64id_fsqrt_d) {
    // 0x5a00f053 : fsqrt.d f0, f1
    test_instruction(0x5a00f053, IN(reg::f1, double(1.1f)), RES(reg::f0, sqrt(double(1.1f))));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fsqrt_s) {
    // 0x5800f053 : fsqrt.s f0, f1
    test_instruction(0x5800f053, IN(reg::f1, float(1.1f)), RES(reg::f0, sqrt(float(1.1f))));
}