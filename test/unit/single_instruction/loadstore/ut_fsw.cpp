#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fsw) {
    // 0x00052a27: 27 2a 05 00   fsw ft0, 20(a0)
    float a = 1.1f;
    uint32_t *addr = (uint32_t *)(GetStackPointer() + 20);
    exec_instruction(0x00052a27, IN(reg::a0, GetStackPointer()), IN(reg::ft0, a));
    EXPECT_EQ(*addr, std::bit_cast<uint32_t>(a));
}
