#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fldsp) {
    double *addr = (double *)(GetSP() + 0);
    addr[0] = double(0.23456f);
    addr[1] = double(1.23456f);
    addr[2] = double(2.23456f);
    addr[3] = double(3.23456f);
    addr[4] = double(4.23456f);

    // 0x2402: c.fldsp fs0, 0  ==> fld fs0, 0(sp)
    test_instruction(0x2402, IN(reg::sp, GetSP()), RES(reg::fs0, addr[0]));

    // 0x2422: c.fldsp fs0, 8  ==> fld fs0, 8(sp)
    test_instruction(0x2422, IN(reg::sp, GetSP()), RES(reg::fs0, addr[1]));

    // 0x2442: c.fldsp fs0, 16  ==> fld fs0, 16(sp)
    test_instruction(0x2442, IN(reg::sp, GetSP()), RES(reg::fs0, addr[2]));

    // 0x3402: c.fldsp fs0, 32  ==> fld fs0, 32(sp)
    test_instruction(0x3402, IN(reg::sp, GetSP()), RES(reg::fs0, addr[4]));
}