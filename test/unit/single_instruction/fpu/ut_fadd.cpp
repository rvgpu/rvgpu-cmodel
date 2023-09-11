#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fadd_d) {
    // 0x02107053 : fadd.d f0, f0, f1
    test_instruction(0x02107053, IN(reg::f0, d2ul(double(1.1f))), IN(reg::f1, d2ul(double(2.1f))), RES(reg::f0, d2ul(double(1.1f) + double(2.1f))));
}
TEST_F(ut_inst, decode_and_execute_rv64if_fadd_s) {
    // 0x00107053 : fadd.s f0, f0, f1
    test_instruction(0x00107053, IN(reg::f0, f2ul(float(1.1f))), IN(reg::f1, f2ul(float(2.1f))), RES(reg::f0, f2ul(float(1.1f) + float(2.1f))));
}