#include <gtest/gtest.h>
#include "sm/compute_unit.h"

TEST(load_insn, should_decode_and_execute_rv32i_auipc_correctly) {
    auto cu = new class compute_unit();
    auto mem = (uint32_t*)calloc(2, sizeof(uint32_t));
    //auipc bits: 0x1297
    mem[0] = 0x1297;
    mem[1] = 0xffff;

    auto pc = (uint64_t)(&mem[0]);
    auto fetch = cu->load_insn(pc);
    //next_pc = pc + 4;
    uint64_t next_pc = cu->execute_insn(pc, fetch);

    next_pc = (uint64_t)((uint32_t)next_pc - (uint32_t)pc) + pc;
    //x[rd] = pc + signe_external(bitsp[31:12] << 12)
    auto rd_data = READ_REG(fetch.insn.rd());
    auto pc_constsnt_offset = (uint32_t)rd_data - (uint32_t)pc;

    EXPECT_EQ(fetch.insn.bits(), 0x1297);
    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(pc_constsnt_offset, 0x1000);
}

TEST(load_insn, shoulde_decode_and_execute_rv32i_addi_correcly) {
    auto cu = new class compute_unit();
    auto mem = (uint32_t*)calloc(2, sizeof(uint32_t));
    //addi bits: 0x8193, imm == -2048
    mem[0] = 0x80018193;
    mem[1] = 0xffff;

    auto pc = (uint64_t)(&mem[0]);
    auto fetch = cu->load_insn(pc);

    //write data 0x80003000 to rs1 register for addi inst
    WRITE_REG(fetch.insn.rs1(), 0x80003000);

    //x[rd] = x[rs1] + sext(immediate)
    uint64_t next_pc = cu->execute_insn(pc, fetch);
    next_pc = (uint64_t)((uint32_t)next_pc - (uint32_t)pc) + pc;
    uint32_t result = READ_REG(fetch.insn.rd());

    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(result, 0x80002800);
}

TEST(load_insn, shoulde_decode_and_execute_rv32i_li_correcly) {
    auto cu = new class compute_unit();
    auto mem = (uint32_t*)calloc(2, sizeof(uint32_t));
    //li bits: 0x02000e93, imm == 32 , dst == x32
    mem[0] = 0x02000e93;
    mem[1] = 0xffff;
    auto pc = (uint64_t)(&mem[0]);

    auto fetch = cu->load_insn(pc);
    // load immediate data, execute addi actually, which equal to x[rd] = x0 + sext(imm)
    uint64_t next_pc = cu->execute_insn(pc, fetch);

    next_pc = (uint64_t)((uint32_t)next_pc - (uint32_t)pc) + pc;
    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(res, 0x20);
}

TEST(load_insn, shoulde_decode_and_execute_rv32i_lui_correcly) {
    auto cu = new class compute_unit();
    auto mem = (uint32_t*)calloc(2, sizeof(uint32_t));
    //li bits: 0x02000e93, imm == 32 , dst == x32
    mem[0] = 0x00002eb7;
    mem[1] = 0xffff;
    auto pc = (uint64_t)(&mem[0]);

    auto fetch = cu->load_insn(pc);

    uint64_t next_pc = cu->execute_insn(pc, fetch);
    next_pc = (uint64_t)((uint32_t)next_pc - (uint32_t)pc) + pc;

    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(res, 0x2000);
}