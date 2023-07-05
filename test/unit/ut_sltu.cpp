#include <gtest/gtest.h>
#include "ut_insns.hpp"

TEST_F(ut_insns, decode_and_execute_snez_rd_reg_should_set_to_1) {
    // snez: 0xa03533;
    // SNEZ rd, rs;  says: rs != 0 ? write 1 to rd : write 0 to rd;  which is assembler pseudoinstruction
    // is same with SLTU
    insts.push_back(0xa03533);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0);
    WRITE_REG(fetch.insn.rs2(), 1);

    ExecuateInst();
    EXPECT_EQ(1, READ_REG(fetch.insn.rd()));
}

TEST_F(ut_insns, decode_and_execute_snez_rd_reg_should_set_to_0) {
    insts.push_back(0xa03533);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0);
    WRITE_REG(fetch.insn.rs2(), 0);

    ExecuateInst();
    EXPECT_EQ(0, READ_REG(fetch.insn.rd()));
}

