#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_flt_d) {
    // 0xa2101553  flt.d a0, ft0, ft1
    insts.push_back(0xa2101553);

    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(2.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);

    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0);

    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(2.1));
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0);
}

TEST_F(ut_inst, decode_and_execute_rv64if_flt_s) {
    // 0xa0101553  flt.s a0, ft0, ft1
    insts.push_back(0xa0101553);

    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(2.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);

    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0);

    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(2.1f));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0);
}