#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_ld) {
    // 0x39813a03 : ld s4, 920(sp)

    // Base = sp, offset = 920 / 8 = 115
    int64_t *addr = (int64_t *)(sp);
    addr[115] = 1234;

    insts.push_back(0x39813a03);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), reinterpret_cast<uint64_t>(addr));
    ExecuateInst();
    uint64_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 1234);
}