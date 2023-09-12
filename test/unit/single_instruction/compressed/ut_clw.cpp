#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_lw) {
    // 0x5108: c.lw a0, 32(a0)
    uint32_t *addr = (uint32_t *)(GetSP() + 32);
    *addr = 0x12345678;
    test_instruction(0x5108, IN(reg::a0, GetSP()), RES(reg::a0, 0x12345678));
}