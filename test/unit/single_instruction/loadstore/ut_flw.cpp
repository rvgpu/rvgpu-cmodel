#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_flw) {
    // 0x0045a007:   07 a0 45 00   flw ft0, 4(a1)
    float a = 1.1f;

    uint64_t addr = GetSP() + 4;
    WriteVRAM<uint32_t>(addr, std::bit_cast<uint32_t>(a));

    test_instruction(0x0045a007, IN(reg::a1, GetSP()), RES(reg::ft0, a));
}
