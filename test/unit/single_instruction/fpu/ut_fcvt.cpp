#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_l) {
    // 0xd2257053 fcvt.d.l   ft0, a0
    insts.push_back(0xd2257053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_lu) {
    // 0xd2357053 fcvt.d.lu   ft0, a0
    insts.push_back(0xd2357053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_s) {
    // 0x4200f053       fcvt.d.s   f0, f1
    insts.push_back(0x4200f053);
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();

    uint64_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<double>(res), 1.1);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_w) {
    // 0xd2057053 fcvt.d.w   ft0, a0
    insts.push_back(0xd2057053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_wu) {
    // 0xd2157053 fcvt.d.wu   ft0, a0
    insts.push_back(0xd2157053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_l_d) {
    // 0xc2201553       fcvt.l.d   a0, ft0, rtz
    insts.push_back(0xc2201553);
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_l_s) {
    // 0xc0201553       fcvt.l.s   a0, ft0, rtz
    insts.push_back(0xc0201553);
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_lu_d) {
    // 0xc2301553       fcvt.lu.d   a0, ft0, rtz
    insts.push_back(0xc2301553);
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_lu_s) {
    // 0xc0301553       fcvt.lu.s   a0, ft0, rtz
    insts.push_back(0xc0301553);
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_s_d) {
    // 0x4010f053       fcvt.s.d   f0, f1
    insts.push_back(0x4010f053);
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();

    uint32_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 1.1f);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_l) {
    // 0xd0257053 fcvt.s.w   ft0, a0
    insts.push_back(0xd0257053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3f800000);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_lu) {
    // 0xd0357053 fcvt.s.lu   ft0, a0
    insts.push_back(0xd0357053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3f800000);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_w) {
    // 0xd0057053 fcvt.s.w   ft0, a0
    insts.push_back(0xd0057053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3f800000);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_wu) {
    // 0xd0157053 fcvt.s.wu   ft0, a0
    insts.push_back(0xd0157053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3f800000);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_w_d) {
    // 0xc2001553       fcvt.w.d   a0, ft0, rtz
    insts.push_back(0xc2001553);
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_w_s) {
    // 0xc0001553       fcvt.w.s   a0, ft0, rtz
    insts.push_back(0xc0001553);
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_wu_d) {
    // 0xc2101553       fcvt.wu.d   a0, ft0, rtz
    insts.push_back(0xc2101553);
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_wu_s) {
    // 0xc0101553       fcvt.wu.s   a0, ft0, rtz
    insts.push_back(0xc0101553);
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}