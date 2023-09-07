#include "ut_inst.hpp"

#define check_caddi(inst, rd, data, result) do { \
    insts.push_back(inst);                      \
    SetIReg(rd, data);                          \
    ExecuateInst();                             \
    uint64_t res = GetIReg(rd);                 \
    EXPECT_EQ(res, result);                     \
} while(0)

TEST_F(ut_inst, decode_and_execuate_caddi) {
    check_caddi(0x1141, reg::sp, 0, GetStackPointer() - 16);   // 0x1141: addi    sp, sp, -16
    check_caddi(0x07c1, reg::a5, 2, 2 + 16); // 0x07c1: addi a5, a5, 16
}