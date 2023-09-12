#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fsdsp) {
    double *addr = (double *)(GetSP());
    // 0xa822: c.fsdsp fs0, 16  ==> fsd fs0, 16(sp) 0x00812827
    exec_instruction(0xa822, IN(reg::fs0, double(0.12345f)), IN(reg::sp, GetSP()));
    EXPECT_DOUBLE_EQ(addr[2], double(0.12345f));
}