#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fsd) {
    // 0xb100: c.fsd fs0, 32(a0)
    exec_instruction(0xb100, IN(reg::a0, GetSP()), IN(reg::fs0, 1.2345678));
    uint64_t result = ReadVRAM<uint64_t>(GetSP() + 32);

    EXPECT_DOUBLE_EQ(std::bit_cast<double>(result), 1.2345678);
}