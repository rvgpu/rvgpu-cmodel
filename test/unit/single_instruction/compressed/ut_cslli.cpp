#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_slli) {
    test_instruction(0x0506, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 1)); // 0x0506: c.slli a0, 1
    test_instruction(0x050a, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 2)); // 0x050a: c.slli a0, 2
    test_instruction(0x050e, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 3)); // 0x050e: c.slli a0, 3
    test_instruction(0x0512, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 4)); // 0x0512: c.slli a0, 4
    test_instruction(0x0522, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 8)); // 0x0522: c.slli a0, 8
    test_instruction(0x0542, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 16)); // 0x0542: c.slli a0, 16
    test_instruction(0x1502, IN(reg::a0, 0x9876543210), RES(reg::a0, 0x9876543210 << 32)); // 0x1502: c.slli a0, 32
}