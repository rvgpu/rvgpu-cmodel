#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_fldsp) {
    uint64_t addr = GetSP();
    WriteVRAM<uint64_t>(addr + 0 * 8, std::bit_cast<uint64_t>(0.123456));
    WriteVRAM<uint64_t>(addr + 1 * 8, std::bit_cast<uint64_t>(1.123456));
    WriteVRAM<uint64_t>(addr + 2 * 8, std::bit_cast<uint64_t>(2.123456));
    WriteVRAM<uint64_t>(addr + 4 * 8, std::bit_cast<uint64_t>(4.123456));

    // 0x2402: c.fldsp fs0, 0  ==> fld fs0, 0(sp)
    test_instruction(0x2402, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint64_t>(addr + 0 * 8)));
    // test_instruction(0x2402, IN(reg::sp, GetSP()), RES(reg::fs0, addr[0]));

    // 0x2422: c.fldsp fs0, 8  ==> fld fs0, 8(sp)
    test_instruction(0x2422, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint64_t>(addr + 1 * 8)));
    // test_instruction(0x2422, IN(reg::sp, GetSP()), RES(reg::fs0, addr[1]));

    // 0x2442: c.fldsp fs0, 16  ==> fld fs0, 16(sp)
    test_instruction(0x2442, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint64_t>(addr + 2 * 8)));
    // test_instruction(0x2442, IN(reg::sp, GetSP()), RES(reg::fs0, addr[2]));

    // 0x3402: c.fldsp fs0, 32  ==> fld fs0, 32(sp)
    test_instruction(0x3402, IN(reg::sp, GetSP()), RES(reg::fs0, ReadVRAM<uint64_t>(addr + 4 * 8)));
    // test_instruction(0x3402, IN(reg::sp, GetSP()), RES(reg::fs0, addr[4]));
}