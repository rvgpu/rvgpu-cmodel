#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_lw) {
    // 0x00c92503 : lw a0, 12(s2)

    // Base = addr, offset = 12 / 4 = 3
    int32_t *addr = (int32_t *) malloc(4 * sizeof(int32_t));
    addr[3] = 1234;

    insts.push_back(0x00c92503);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), reinterpret_cast<uint64_t>(addr));
    ExecuateInst();
    uint64_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 1234);
}