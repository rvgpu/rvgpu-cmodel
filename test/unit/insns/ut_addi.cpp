#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_rv32_insns, shoulde_decode_and_execute_rv32i_addi_correcly) {
    //addi bits: 0x8193, imm == -2048
    insts.push_back(0x80018193);
    LoadInst();

    //write data 0x80003000 to rs1 register for addi inst
    WRITE_REG(fetch.insn.rs1(), 0x80003000);

    ExecuateInst();

    //x[rd] = x[rs1] + sext(immediate)
    uint32_t result = READ_REG(fetch.insn.rd());
    EXPECT_EQ(result, 0x80002800);
}

TEST_F(ut_rv64_insns, shoulde_decode_and_execute_addi_correcly) {
    //addi bits: 0xfff50513  #addi a0, a0, -1
    insts.push_back(0xfff50513);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 1);
    ExecuateInst();
    uint64_t result = READ_REG(fetch.insn.rd());
    EXPECT_EQ(result, 0);
}