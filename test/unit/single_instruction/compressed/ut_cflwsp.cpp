#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_flwsp) {
    float *addr = (float *)(GetSP() + 0);
    addr[0] = float(0.123456f);
    addr[1] = float(1.123456f);
    addr[2] = float(2.123456f);
    addr[3] = float(3.123456f);

    // 0x6402: c.flwsp fs0, 0  ==> flw fs0, 0(sp)
    test_instruction(0x6402, IN(reg::sp, GetSP()), RES(reg::fs0, addr[0]));
    // 0x6412: c.flwsp fs0, 4  ==> flw fs0, 4(sp)
    test_instruction(0x6412, IN(reg::sp, GetSP()), RES(reg::fs0, addr[1]));
    // 0x6422: c.flwsp fs0, 8  ==> flw fs0, 8(sp)
    test_instruction(0x6422, IN(reg::sp, GetSP()), RES(reg::fs0, addr[2]));
    // 0x6432: c.flwsp fs0, 12  ==> flw fs0, 12(sp)
    test_instruction(0x6432, IN(reg::sp, GetSP()), RES(reg::fs0, addr[3]));
}