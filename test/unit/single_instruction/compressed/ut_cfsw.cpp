#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fsw) {
    // 0xf100: c.fsw fs0, 32(a0)
    exec_instruction(0xf100, IN(reg::fs0, float(2.34567f)), IN(reg::a0, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(GetSP() + 32);

    EXPECT_FLOAT_EQ(std::bit_cast<float>(result), float(2.34567f));
}