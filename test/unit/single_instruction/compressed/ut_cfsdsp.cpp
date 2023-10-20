#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fsdsp) {
    // 0xa822: c.fsdsp fs0, 16  ==> fsd fs0, 16(sp) 0x00812827
    uint64_t addr = GetSP();

    exec_instruction(0xa822, IN(reg::fs0, 0.12345), IN(reg::sp, GetSP()));
    uint64_t result = ReadVRAM<uint64_t>(GetSP() + 16);

    EXPECT_DOUBLE_EQ(std::bit_cast<double>(result), 0.12345);
}