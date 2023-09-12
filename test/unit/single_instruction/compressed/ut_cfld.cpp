#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fld) {
    double *addr = (double *)(GetSP() + 16);
    *addr = double(1.234f);

    // 0x2900: c.fld fs0, 16(a0)
    test_instruction(0x2900, IN(reg::a0, GetSP()), RES(reg::fs0, double(1.234f)));
}