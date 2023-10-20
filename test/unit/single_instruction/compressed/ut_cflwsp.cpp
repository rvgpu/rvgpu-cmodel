#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_flwsp) {
    uint64_t addr = GetSP();
    WriteVRAM<uint32_t>(addr + 0 * 4, std::bit_cast<uint32_t>(0.123456f));
    WriteVRAM<uint32_t>(addr + 1 * 4, std::bit_cast<uint32_t>(1.123456f));
    WriteVRAM<uint32_t>(addr + 2 * 4, std::bit_cast<uint32_t>(2.123456f));
    WriteVRAM<uint32_t>(addr + 3 * 4, std::bit_cast<uint32_t>(3.123456f));

    // 0x6402: c.flwsp fs0, 0  ==> flw fs0, 0(sp)
    test_instruction(0x6402, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint32_t>(addr + 0 * 4)));

    // 0x6412: c.flwsp fs0, 4  ==> flw fs0, 4(sp)
    test_instruction(0x6412, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint32_t>(addr + 1 * 4)));

    // 0x6422: c.flwsp fs0, 8  ==> flw fs0, 8(sp)
    test_instruction(0x6422, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint32_t>(addr + 2 * 4)));

    // 0x6432: c.flwsp fs0, 12  ==> flw fs0, 12(sp)
    test_instruction(0x6432, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint32_t>(addr + 3 * 4)));
}