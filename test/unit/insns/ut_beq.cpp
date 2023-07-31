#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_BRANCH(a) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        ExecuateInst();           \
        auto pc = Getpc();        \
        auto next_pc = GetNextpc(); \
        if (a == 0) { \
            EXPECT_EQ(next_pc, pc - 84); \
        } else { \
            EXPECT_EQ(next_pc, pc + 4); \
        } \
    } while(0)


TEST_F(ut_insns, decode_and_execute_rv64i_beq) {
    // 0xfa0506e3 : beqz a0, -84 (beq a0, x0, -84)
    insts.push_back(0xfa0506e3);
    auto pc = (uint64_t)insts.data();
    printf("start pc: %lx\n", pc);

    SetIReg(reg::a0, 1);
    ExecuateInst();
    printf("pc: %lx\n", GetPC());
    EXPECT_EQ(GetPC(), pc + 4);

    SetIReg(reg::a0, 0);
    ExecuateInst();
    EXPECT_EQ(GetPC(), pc - 84);

    SetIReg(reg::a0, -1);
    ExecuateInst();
    EXPECT_EQ(GetPC(), pc + 4);

    SetIReg(reg::a0, 12);
    ExecuateInst();
    EXPECT_EQ(GetPC(), pc + 4);

    SetIReg(reg::a0, -12);
    ExecuateInst();
    EXPECT_EQ(GetPC(), pc + 4);
}