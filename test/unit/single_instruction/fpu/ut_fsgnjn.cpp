#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fsgnjn_d) {
    // 0x22101053 : fsgnjn.d f0, f0, f1
    insts.push_back(0x22101053);

    uint64_t res = 0;

    SetFReg(fpreg::f0, std::bit_cast<uint64_t>(1.1));
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(2.1));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<double>(res), -1.1);

    SetFReg(fpreg::f0, std::bit_cast<uint64_t>(1.1));
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(-2.1));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<double>(res), 1.1);

    SetFReg(fpreg::f0, std::bit_cast<uint64_t>(-1.1));
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(2.1));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<double>(res), -1.1);

    SetFReg(fpreg::f0, std::bit_cast<uint64_t>(-1.1));
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(-2.1));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<double>(res), 1.1);
}


TEST_F(ut_inst, decode_and_execute_rv64if_fsgnjn_s) {
    // 0x20101053 : fsgnjn.s f0, f0, f1
    insts.push_back(0x20101053);

    uint32_t res = 0;

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), -1.1f);

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(-2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 1.1f);

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(-1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), -1.1f);

    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(-1.1f));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(-2.1f));
    ExecuateInst();
    res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 1.1f);
}