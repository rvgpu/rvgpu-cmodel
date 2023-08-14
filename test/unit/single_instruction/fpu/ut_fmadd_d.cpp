#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmadd_d) {
    // 0x0220f043 : fmadd.d ft0, ft1, ft2, ft0
    insts.push_back(0x0220f043);

    double a = 1.1f;
    double b = 2.1f;
    double c = 3.1f;
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(a));
    SetFReg(fpreg::ft2, std::bit_cast<uint64_t>(b));
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(c));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), a * b + c);
}