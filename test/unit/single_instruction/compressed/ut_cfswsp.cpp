#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fswsp) {
    // 0xe822: c.fswsp fs0, 16  ==> fsw fs0, 16(sp)
    uint64_t addr = GetSP();

    exec_instruction(0xe822, IN(reg::fs0, 0.12345f), IN(reg::sp, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(GetSP() + 16);

    EXPECT_DOUBLE_EQ(std::bit_cast<float>(result), 0.12345f);
}