#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_lwu) {
    // 0x01456603 : lwu a2, 20(a0)
    uint64_t addr = GetSP() + 20;
    WriteVRAM<uint32_t>(addr, 0x10001000);

    test_instruction(0x01456603, IN(reg::a0, GetSP()), RES(reg::a2, 0x10001000));
}