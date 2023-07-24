#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_lwu) {
    // 0x01456603 : lwu a2, 20(a0)

    // Base = addr, offset = 20 / 4 = 5
    uint32_t *addr = (uint32_t *) malloc(6 * sizeof(uint32_t));
    addr[5] = 1234;

    insts.push_back(0x01456603);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), reinterpret_cast<uint64_t>(addr));
    ExecuateInst();
    uint64_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 1234);
}