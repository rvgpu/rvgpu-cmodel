#include "ut_inst.hpp"

static inline uint64_t sraw(uint64_t a, uint64_t b)
{
    uint64_t res = int32_t(int32_t(a) >> (b & 0x1F));
    return res;
}

TEST_F(ut_inst, decode_and_execute_rv64i_sra){
    // 0x40c5d53b       sraw    a0, a1, a2
    insts.push_back(0x40c5d53b);

    uint64_t a = 0x87654321000;
    uint64_t b = 0x8;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, b);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), sraw(a, b));
}