#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_flw) {
    // 0x0045a007:   07 a0 45 00   flw ft0, 4(a1)
    insts.push_back(0x0045a007);

    uint32_t *addr = (uint32_t *)(GetStackPointer() + 4);
    *addr = std::bit_cast<uint32_t>(1.1f);

    auto regr = fpreg::ft0;
    uint32_t result = 0;
    SetIReg(reg::a1, GetStackPointer());
    ExecuateInst();
    result = GetFReg(regr);
    EXPECT_EQ(std::bit_cast<float>(result), 1.1f);
}
