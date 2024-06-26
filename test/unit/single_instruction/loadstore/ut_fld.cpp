#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fld) {
    // 0x0045b007: fld ft0, 4(a1)
    double a = 1.1f;

    uint64_t addr = GetSP() + 4;
    WriteVRAM<uint64_t>(addr, std::bit_cast<uint64_t>(a));

    test_instruction(0x0045b007, IN(reg::a1, GetSP()), RES(reg::ft0, a));
}
