#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmsub_d) {
    // 0x22107247   fmsub.d ft4, ft0, ft1, ft4
    double a = 1.1f;
    double b = 2.1f;
    double c = 3.3f;
    test_instruction(0x22107247, IN(reg::ft0, a), IN(reg::ft1, b), IN(reg::ft4, c), RES(reg::ft4, a * b - c));
}
TEST_F(ut_inst, decode_and_execute_rv64if_fmsub_s) {
    // 0x20107247   fmsub.s ft4, ft0, ft1, ft4
    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    test_instruction(0x20107247, IN(reg::ft0, a), IN(reg::ft1, b), IN(reg::ft4, c), RES(reg::ft4, a * b - c));
}