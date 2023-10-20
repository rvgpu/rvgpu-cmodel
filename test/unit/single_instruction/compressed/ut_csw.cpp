#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_sw) {
    // 0xd188: c.sw a0, 32(a1)
    exec_instruction(0xd188, IN(reg::a0, 0x12345678), IN(reg::a1, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(GetSP() + 32);

    EXPECT_EQ(result, 0x12345678);
}