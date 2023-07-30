#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

#define CHECK_ADD(a, b) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        ExecuateInst();           \
        result = READ_REG(fetch.insn.rd()); \
        EXPECT_EQ(result, (a + b)); \
    } while(0)

TEST_F(ut_insns, decode_and_execute_rv64i_pseudo_li) {
    // 0x07f00513 : li a0, 127 (addi x10, x0, 127)
    insts.push_back(0x07f00513);
    SetIReg(reg::x0, 0x0);
    ExecuateInst();

    uint64_t result = GetIReg(reg::x10);
    EXPECT_EQ(result, 127);
}