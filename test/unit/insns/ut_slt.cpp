#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_exec_sgtz_should_set_0) {
    //bits: 0x00a02ab3    #sgtz s5, a0
    //sgtz is pseudoinstructions inst, same as: slt rd, x0, rs, Set if > zero
    insts.push_back(0x00a02ab3);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0);
    WRITE_REG(fetch.insn.rs2(), 0xffffffffffffffff);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rd());
    EXPECT_EQ(res, 0);
}

TEST_F(ut_rv64_insns, decode_and_exec_sgtz_should_set_1) {
    //bits: 0x00a02ab3    #sgtz s5, a0
    //sgtz is pseudoinstructions inst, same as: slt rd, x0, rs, Set if > zero
    insts.push_back(0x00a02ab3);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0);
    WRITE_REG(fetch.insn.rs2(), 0x7fffffffffffffff);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rd());
    EXPECT_EQ(res, 1);
}
