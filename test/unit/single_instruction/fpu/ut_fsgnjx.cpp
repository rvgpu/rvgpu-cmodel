#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fsgnjx_d) {
    // 0x22102053 : fsgnjx.d f0, f0, f1
    test_instruction(0x22102053, IN(reg::f0, double(1.1f)), IN(reg::f1, double(2.1)), RES(reg::f0, double(1.1f)));
    test_instruction(0x22102053, IN(reg::f0, double(1.1f)), IN(reg::f1, double(-2.1)), RES(reg::f0, double(-1.1f)));
    test_instruction(0x22102053, IN(reg::f0, double(-1.1f)), IN(reg::f1, double(2.1)), RES(reg::f0, double(-1.1f)));
    test_instruction(0x22102053, IN(reg::f0, double(-1.1f)), IN(reg::f1, double(-2.1)), RES(reg::f0, double(1.1f)));
}


TEST_F(ut_inst, decode_and_execute_rv64if_fsgnjx_s) {
    // 0x20102053 : fsgnjx.s f0, f0, f1
    test_instruction(0x20102053, IN(reg::f0, float(1.1f)), IN(reg::f1, float(2.1)), RES(reg::f0, float(1.1f)));
    test_instruction(0x20102053, IN(reg::f0, float(1.1f)), IN(reg::f1, float(-2.1)), RES(reg::f0, float(-1.1f)));
    test_instruction(0x20102053, IN(reg::f0, float(-1.1f)), IN(reg::f1, float(2.1)), RES(reg::f0, float(-1.1f)));
    test_instruction(0x20102053, IN(reg::f0, float(-1.1f)), IN(reg::f1, float(-2.1)), RES(reg::f0, float(1.1f)));
}