#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_ld) {
    // 0x01015503: lb a0, 16(sp)
    insts.push_back(0x01015503);

    uint32_t *addr = (uint32_t *)(GetStackPointer() + 16);
    *addr = 0x12345678;

    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0x5678);
}