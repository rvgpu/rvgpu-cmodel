#include <gtest/gtest.h>
#include "sm/compute_unit.h"

TEST(test_inst, should_decode_and_execute_sw_correctly) {
    auto p = new class compute_unit();
    auto mem = (uint32_t*)calloc(1200, sizeof(uint32_t));
    //sw bits: 0x48112623
    mem[0] = 0x48112623;

    auto sp = (uint32_t*)malloc(sizeof(uint32_t));
    uint32_t sp_high = (uint64_t)sp & (0xffffffffLU << 32U);
    uint32_t sp_low = (uint64_t)sp & 0xffffffff;

    MMU.set_base_addr(sp_high);

    auto pc = (uint64_t)(&mem[0]);
    auto fetch = p->load_insn(pc);
    WRITE_REG(fetch.insn.rs1(), sp_low);
    WRITE_REG(fetch.insn.rs2(), 333);

    uint64_t next_pc = p->execute_insn(pc, fetch);

    EXPECT_EQ(next_pc, pc + 4);
    EXPECT_EQ(*(uint32_t*)((uint64_t)sp + 1164), 333);
}