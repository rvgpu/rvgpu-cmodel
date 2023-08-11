#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64_div) {
    // 0x02c5c533 : div a0, a1, a2
    insts.push_back(0x02c5c533);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), a / 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), int64_t(a) / (-4));
}

TEST_F(ut_inst, decode_and_execute_rv64_divu) {
    // 0x02c5d533 : divu a0, a1, a2
    insts.push_back(0x02c5d533);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), a / 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint64_t(a) / uint64_t(-4));
}

TEST_F(ut_inst, decode_and_execute_rv64_divw) {
    // 0x02c5c53b : divw a0, a1, a2
    insts.push_back(0x02c5c53b);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), int32_t(a) / 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), int32_t(a) / int32_t(-4));
}

TEST_F(ut_inst, decode_and_execute_rv64_divuw) {
    // 0x02c5d53b : div a0, a1, a2
    insts.push_back(0x02c5d53b);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint32_t(a) / 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint32_t(a) / uint32_t(-4));
}