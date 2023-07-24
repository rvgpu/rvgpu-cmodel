#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv32_insns, decode_and_execute_rv32i_sw) {
    //sw bits: 0x48112623
    insts.push_back(0x48112623);
    uint32_t sp_low = (uint64_t)sp & 0xffffffff;
    LoadInst();

    WRITE_REG(fetch.insn.rs1(), sp_low);
    WRITE_REG(fetch.insn.rs2(), 333);

    ExecuateInst();
    EXPECT_EQ(*(uint32_t*)((uint64_t)sp + 1164), 333);
}

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_sw){
    //sw bits: 0x00c52823 # sw  a2, 16(a0)
    insts.push_back(0x00c52823);
    LoadInst();

    WRITE_REG(fetch.insn.rs1(), (uint64_t)sp);
    WRITE_REG(fetch.insn.rs2(), (uint64_t)333);

    ExecuateInst();
    EXPECT_EQ(*(uint32_t*)((uint64_t)sp + 16), 333);
}