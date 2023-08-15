#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fsgnj_s) {
    // 0x20100053 : fsgnj.s f0, f0, f1
    insts.push_back(0x20100053);

    uint32_t res = 0;

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 1.1f);

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(-2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), -1.1f);

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(-1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 1.1f);

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(-1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(-2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), -1.1f);
}