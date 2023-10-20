#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fld) {
    // 0x2900: c.fld fs0, 16(a0)
    uint64_t addr = GetSP() + 16;
    WriteVRAM<uint64_t>(addr, std::bit_cast<uint64_t>(1.234));

    test_instruction(0x2900, IN(reg::a0, GetSP()), RES(reg::fs0, 1.234));
}