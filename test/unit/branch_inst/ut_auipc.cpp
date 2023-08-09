#include "ut_branch.hpp"

TEST_F(ut_branch, decode_and_execute_rv64i_auipc) {
    //auipc bits: 0x97; auipc  ra, 0
    insts.push_back(0x97);
    ExecuateInst();

    // ra = pc + 4
    // pc = pc + 0
    auto pc = (uint64_t)insts.data();
    EXPECT_EQ(GetIReg(reg::ra), pc + 0);
    EXPECT_EQ(GetPC(), pc + 4);
}