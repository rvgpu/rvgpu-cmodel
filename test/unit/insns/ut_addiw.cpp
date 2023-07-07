#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_ADD(a, b) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        ExecuateInst();           \
        result = READ_REG(fetch.insn.rd()); \
        EXPECT_EQ(result, (a + b)); \
    } while(0)

TEST_F(ut_rv64_insns, should_decode_and_execute_rv64i_add_correctly) {
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