#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmadd_d) {
    // 0x0220f043 : fmadd.d ft0, ft1, ft2, ft0
    test_instruction(0x0220f043,
                     IN(reg::ft1, double(1.1f)),
                     IN(reg::ft2, double(2.1f)),
                     IN(reg::ft0, double(3.1f)),
                     RES(reg::ft0, double(1.1f) * double(2.1f) + double(3.1f)));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmadd_s) {
    // 0x0020f043 : fmadd.s ft0, ft1, ft2, ft0
    test_instruction(0x0020f043,
                     IN(reg::ft1, float(1.1f)),
                     IN(reg::ft2, float(2.1f)),
                     IN(reg::ft0, float(3.1f)),
                     RES(reg::ft0, float(1.1f) * float(2.1f) + float(3.1f)));
}