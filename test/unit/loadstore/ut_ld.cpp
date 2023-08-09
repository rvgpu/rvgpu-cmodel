#include "ut_loadstore.hpp"

TEST_F(ut_loadstore, decode_and_execute_rv64i_ld) {
    // 0x39813a03 : ld s4, 920(sp)
    insts.push_back(0x39813a03);

    int64_t *addr = (int64_t *)(GetStackPointer() + 920);
    *addr = 0x1000100010001000;

    auto regr = reg::s4;
    int64_t result = 0;
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0x1000100010001000);
}