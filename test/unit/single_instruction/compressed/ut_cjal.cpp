#include "ut_inst.hpp"

#define check_cjal(inst, imm) do { \
    insts.push_back(inst);         \
    pc = (uint64_t)insts.data();   \
    ExecuateInst();                \
    EXPECT_EQ(GetPC(), pc + imm);  \
} while(0)

TEST_F(ut_inst, decode_and_execuate_cjal) {
    uint64_t pc = 0;

    check_cjal(0x2801, 16);   // 0x2801: cjal 16
}