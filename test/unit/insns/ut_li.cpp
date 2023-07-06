#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_rv32_insns, shoulde_decode_and_execute_rv32i_li_correcly) {
    //li bits: 0x02000e93, imm == 32 , dst == x32
    insts.push_back(0x02000e93);
    LoadInst();

    ExecuateInst();

    // load immediate data, execute addi actually, which equal to x[rd] = x0 + sext(imm)
    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 0x20);
}

TEST_F(ut_rv32_insns, shoulde_decode_and_execute_rv32i_lui_correcly) {
    //li bits: 0x02000e93, imm == 32 , dst == x32
    insts.push_back(0x00002eb7);
    LoadInst();

    ExecuateInst();

    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 0x2000);
}