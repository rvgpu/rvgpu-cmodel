#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_l) {
    // 0xd2257053 fcvt.d.l   ft0, a0
    test_instruction(0xd2257053, IN(reg::a0, 1), RES(reg::ft0, d2ul(double(1))));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_lu) {
    // 0xd2357053 fcvt.d.lu   ft0, a0
    test_instruction(0xd2357053, IN(reg::a0, 1), RES(reg::ft0, d2ul(double(1))));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_s) {
    // 0x4200f053       fcvt.d.s   f0, f1
    test_instruction(0x4200f053, IN(reg::f1, f2ui(float(1.1f))), RES(reg::f0, d2ul(double(1.1f))));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_w) {
    // 0xd2057053 fcvt.d.w   ft0, a0
    test_instruction(0xd2057053, IN(reg::a0, 1), RES(reg::ft0, d2ul(double(1))));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_wu) {
    // 0xd2157053 fcvt.d.wu   ft0, a0
    test_instruction(0xd2157053, IN(reg::a0, 1), RES(reg::ft0, d2ul(double(1))));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_l_d) {
    // 0xc2201553       fcvt.l.d   a0, ft0, rtz
    test_instruction(0xc2201553, IN(reg::ft0, d2ul(double(1.1f))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_l_s) {
    // 0xc0201553       fcvt.l.s   a0, ft0, rtz
    test_instruction(0xc0201553, IN(reg::ft0, f2ul(float(1.1f))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_lu_d) {
    // 0xc2301553       fcvt.lu.d   a0, ft0, rtz
    test_instruction(0xc2301553, IN(reg::ft0, d2ul(double(1.1f))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_lu_s) {
    // 0xc0301553       fcvt.lu.s   a0, ft0, rtz
    test_instruction(0xc0301553, IN(reg::ft0, f2ul(float(1.1f))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_s_d) {
    // 0x4010f053       fcvt.s.d   f0, f1
    test_instruction(0x4010f053, IN(reg::f1, d2ul(double(1.1f))), RES(reg::f0, f2ul(float(1.1f))));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_l) {
    // 0xd0257053 fcvt.s.w   ft0, a0
    test_instruction(0xd0257053, IN(reg::a0, 1), RES(reg::ft0, f2ul(float(1.0f))));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_lu) {
    // 0xd0357053 fcvt.s.lu   ft0, a0
    test_instruction(0xd0357053, IN(reg::a0, 1), RES(reg::ft0, f2ul(float(1.0f))));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_w) {
    // 0xd0057053 fcvt.s.w   ft0, a0
    test_instruction(0xd0057053, IN(reg::a0, 1), RES(reg::ft0, f2ul(float(1.0f))));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_wu) {
    // 0xd0157053 fcvt.s.wu   ft0, a0
    test_instruction(0xd0157053, IN(reg::a0, 1), RES(reg::ft0, f2ul(float(1.0f))));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_w_d) {
    // 0xc2001553       fcvt.w.d   a0, ft0, rtz
    test_instruction(0xc2001553, IN(reg::ft0, d2ul(double(1.1))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_w_s) {
    // 0xc0001553       fcvt.w.s   a0, ft0, rtz
    test_instruction(0xc0001553, IN(reg::ft0, f2ul(float(1.1))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_wu_d) {
    // 0xc2101553       fcvt.wu.d   a0, ft0, rtz
    test_instruction(0xc2101553, IN(reg::ft0, d2ul(double(1.1))), RES(reg::a0, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_wu_s) {
    // 0xc0101553       fcvt.wu.s   a0, ft0, rtz
    test_instruction(0xc0101553, IN(reg::ft0, f2ul(float(1.1))), RES(reg::a0, 1));
}