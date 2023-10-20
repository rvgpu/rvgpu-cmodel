#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_lw) {
    // 0x5108: c.lw a0, 32(a0)
    uint64_t addr = GetSP() + 32;
    WriteVRAM<uint32_t>(addr, 0x12345678);

    test_instruction(0x5108, IN(reg::a0, GetSP()), RES(reg::a0, 0x12345678));
}