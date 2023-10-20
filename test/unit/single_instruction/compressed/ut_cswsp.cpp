#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_swsp) {
    // 0xc82a: c.swsp fs0, 16  ==> sw a0, 16(sp)
    exec_instruction(0xc82a, IN(reg::a0, 0x12345678), IN(reg::sp, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(GetSP() + 16);

    EXPECT_EQ(result, 0x12345678);
}