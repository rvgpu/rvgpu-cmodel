#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_ADD(a, b) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        ExecuateInst();           \
        result = READ_REG(fetch.insn.rd()); \
        EXPECT_EQ(result, (a + b)); \
    } while(0)

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_addiw) {
    // 0x0017071b : addiw a4, a4, 1
    insts.push_back(0x0017071b);
    uint64_t result;
    LoadInst();

    CHECK_ADD(2, 1);
    CHECK_ADD(-2, 1);
    CHECK_ADD(0, 1);
    CHECK_ADD(12, 1);
    CHECK_ADD(-12, 1);    
}

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_pseudo_sextw) {
    //bits: 0x0006869b  #sext.w  a3, a3  pseudoinstruction of addiw rd, rs, 0
    // writes the sign-extension of the lower 32 bits of register rs1 into register rd
    insts.push_back(0x0006869b);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0x111180000001);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rs1());

    EXPECT_EQ(res, 0xffffffff80000001);
}