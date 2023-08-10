#include "ut_inst.hpp"

#define CHECK_SUB(a, b) do {                    \
        uint64_t result = 0;                    \
        SetIReg(rega, a);                       \
        SetIReg(regb, b);                       \
        ExecuateInst();                         \
        result = GetIReg(regr);                 \
        EXPECT_EQ(result, (a - b));             \
    } while(0)

TEST_F(ut_inst, decode_and_execute_rv64i_add) {
    // 0x40b50533        sub a0, a0, a1
    insts.push_back(0x40b50533);
    auto rega = reg::a0;
    auto regb = reg::a1;
    auto regr = reg::a0;

    CHECK_SUB(2, 1);
    CHECK_SUB(1, 2);
    CHECK_SUB(-1, 1);
    CHECK_SUB(-1, 2);
    CHECK_SUB(1, -1);
    CHECK_SUB(1, -2);
}