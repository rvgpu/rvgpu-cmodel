#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_insns, should_decode_and_execute_rv32i_auipc_correctly) {
    //auipc bits: 0x1297
    insts.push_back(0x1297);
    LoadInst();

    ExecuateInst();

    //next_pc = pc + 4;
    //x[rd] = pc + signe_external(bitsp[31:12] << 12)
    auto rd_data = READ_REG(fetch.insn.rd());
    auto pc_constsnt_offset = (uint32_t)rd_data - (uint32_t)pc;

    EXPECT_EQ(fetch.insn.bits(), 0x1297);
    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(pc_constsnt_offset, 0x1000);
}

TEST_F(ut_insns, shoulde_decode_and_execute_rv32i_addi_correcly) {
    //addi bits: 0x8193, imm == -2048
    insts.push_back(0x80018193);
    LoadInst();

    //write data 0x80003000 to rs1 register for addi inst
    WRITE_REG(fetch.insn.rs1(), 0x80003000);

    ExecuateInst();

    //x[rd] = x[rs1] + sext(immediate)
    uint32_t result = READ_REG(fetch.insn.rd());
    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(result, 0x80002800);
}

TEST_F(ut_insns, shoulde_decode_and_execute_rv32i_li_correcly) {
    //li bits: 0x02000e93, imm == 32 , dst == x32
    insts.push_back(0x02000e93);
    LoadInst();

    ExecuateInst();

    // load immediate data, execute addi actually, which equal to x[rd] = x0 + sext(imm)
    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(res, 0x20);
}

TEST_F(ut_insns, shoulde_decode_and_execute_rv32i_lui_correcly) {
    //li bits: 0x02000e93, imm == 32 , dst == x32
    insts.push_back(0x00002eb7);
    LoadInst();

    ExecuateInst();

    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(res, 0x2000);
}
