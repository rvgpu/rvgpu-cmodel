#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_cjal) {
    check_cjal(0x2801, 16);   // 0x2801: cjal 16
    check_cjal(0x3fc5, -16);  // 0x3fc5: c.jal -16
}