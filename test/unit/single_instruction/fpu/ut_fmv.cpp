#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmv_d_x) {
    // 0xf2000053 : fmv.d.x ft0, zero
    test_instruction(0xf2000053, IN(reg::ft0, double(1.1)), RES(reg::ft0, double(0.0f)));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmv_w_x) {
    // 0xf0000053 : fmv.w.x ft0, zero
    test_instruction(0xf0000053, IN(reg::ft0, float(1.1)), RES(reg::ft0, float(0.0f)));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fmv_x_d) {
    // 0xe2000553 : fmv.x.d a0, ft0
    test_instruction(0xe2000553, IN(reg::ft0, double(1.0)), RES(reg::a0, double(1.0f)));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmv_x_w) {
    // 0xe0000553 : fmv.x.w a0, ft0
    test_instruction(0xe0000553, IN(reg::ft0, float(1.0)), RES(reg::a0, float(1.0f)));
}