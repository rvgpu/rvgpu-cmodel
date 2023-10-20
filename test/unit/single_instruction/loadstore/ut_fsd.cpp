#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fsd) {
    // 0x00053a27: fsw ft0, 20(a0)
    double a = 1.1f;

    uint64_t addr = GetSP() + 20;
    exec_instruction(0x00053a27, IN(reg::a0, GetSP()), IN(reg::ft0, a));
    uint64_t result = ReadVRAM<uint64_t>(addr);

    EXPECT_EQ(result, std::bit_cast<uint64_t>(a));
}
