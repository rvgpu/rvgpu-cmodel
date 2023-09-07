#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_caddi) {
    check_cli(0x4541, reg::a0, 16);     // 0x4541: c.li a0, 16
    check_cli(0x5541, reg::a0, -16);     // 0x4541: c.li a0, -16
}