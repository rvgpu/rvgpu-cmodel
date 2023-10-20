#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_flw) {
    // 0x7100: c.flw fs0, 32(a0)
    uint64_t addr = GetSP() + 32;
    WriteVRAM<uint32_t>(addr, std::bit_cast<uint32_t>(1.2345f));

    test_instruction(0x7100, IN(reg::a0, GetSP()), RES(reg::fs0, float(1.2345f)));
}