#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fsd) {
    // 0x00053a27: fsw ft0, 20(a0)
    insts.push_back(0x00053a27);

    uint64_t *addr = (uint64_t *)(GetStackPointer() + 20);

    SetIReg(reg::a0, GetStackPointer());
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    EXPECT_EQ(std::bit_cast<double>(*addr), 1.1);
}
