#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64_rem) {
    // 0x02c5e533 : rem a0, a1, a2
    insts.push_back(0x02c5e533);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), a % 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), int64_t(a) % (-4));
}

TEST_F(ut_inst, decode_and_execute_rv64_remu) {
    // 0x02c5f533 : remu a0, a1, a2
    insts.push_back(0x02c5f533);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), a % 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint64_t(a) % uint64_t(-4));
}

TEST_F(ut_inst, decode_and_execute_rv64_remw) {
    // 0x02c5e53b : remw a0, a1, a2
    insts.push_back(0x02c5e53b);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), int32_t(a) % 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), int32_t(a) % int32_t(-4));
}

TEST_F(ut_inst, decode_and_execute_rv64_remuw) {
    // 0x02c5f53b : remuw a0, a1, a2
    insts.push_back(0x02c5f53b);

    uint64_t a = 0x87654321000;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, 4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint32_t(a) % 4);

    SetIReg(reg::a1, a);
    SetIReg(reg::a2, -4);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint32_t(a) % uint32_t(-4));
}