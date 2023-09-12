#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fswsp) {
    float *addr = (float *)(GetSP());
    // 0xe822: c.fswsp fs0, 16  ==> fsw fs0, 16(sp)
    exec_instruction(0xe822, IN(reg::fs0, float(0.12345f)), IN(reg::sp, GetSP()));
    EXPECT_DOUBLE_EQ(addr[4], float(0.12345f));
}