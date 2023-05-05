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