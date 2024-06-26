#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sd) {
    // bits: 0x00a13c23   sd  a0, 24(sp)
    uint64_t addr = GetSP();

    exec_instruction(0x00a13c23, IN(reg::a0, 0x1000100010001000), IN(reg::sp, GetSP()));
    uint64_t result = ReadVRAM<uint64_t>(addr + 24);

    EXPECT_EQ(result, 0x1000100010001000);
}