#include "ut_loadstore.hpp"

TEST_F(ut_loadstore, decode_and_execute_rv64i_lwu) {
    // 0x01456603 : lwu a2, 20(a0)
    insts.push_back(0x01456603);

    uint32_t *addr = (uint32_t *)(GetStackPointer() + 20);
    *addr = 0x10001000;

    auto regr = reg::a2;
    int32_t result = 0;
    SetIReg(reg::a0, GetStackPointer());
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0x10001000);
}