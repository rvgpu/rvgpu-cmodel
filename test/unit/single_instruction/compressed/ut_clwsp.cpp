#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_lwsp) {
    uint32_t *addr = (uint32_t *)(GetSP() + 0);
    addr[0] = 0x12345678;
    addr[1] = 0x22345678;
    addr[2] = 0x32345678;
    addr[3] = 0x42345678;

    // 0x4502: c.lwsp a0, 0  ==> lw a0, 0(sp)
    test_instruction(0x4502, IN(reg::sp, GetSP()), RES(reg::a0, addr[0]));
    // 0x4512: c.lwsp a0, 0  ==> lw a0, 0(sp)
    test_instruction(0x4512, IN(reg::sp, GetSP()), RES(reg::a0, addr[1]));
    // 0x4522: c.lwsp a0, 8  ==> lw a0, 8(sp)
    test_instruction(0x4522, IN(reg::sp, GetSP()), RES(reg::a0, addr[2]));
    // 0x4532: c.lwsp a0, 12  ==> lw a0, 12(sp)
    test_instruction(0x4532, IN(reg::sp, GetSP()), RES(reg::a0, addr[3]));
}