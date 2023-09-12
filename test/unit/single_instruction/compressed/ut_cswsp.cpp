#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_add) {
    uint32_t *addr = (uint32_t *)(GetSP());
    // 0xc82a: c.swsp fs0, 16  ==> sw a0, 16(sp)
    exec_instruction(0xc82a, IN(reg::a0, 0x12345678), IN(reg::sp, GetSP()));
    EXPECT_DOUBLE_EQ(addr[4], 0x12345678);
}