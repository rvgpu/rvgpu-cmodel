#include <gtest/gtest.h>
#include "rcore/rcore.hpp"
#include "simt/simt.hpp"
#include "inst.hpp"

TEST_F(inst, decode_cvt_f32_i32) {
    // v_cvt_f32_i32_e32 v2, s0
    inst_init(0x7E040A00);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());

    EXPECT_EQ(res->type, VOP1);
    EXPECT_EQ(res->op, 5);
    EXPECT_EQ(res->src0_id, 0);
    EXPECT_EQ(res->dst_id, 2);
}

TEST_F(inst, exe_cvt_f32_i32) {
    rinst_issue issued{};
    issued.type = VOP1;
    issued.src0[0] = 1;
    issued.op = 5;

    auto res = dynamic_pointer_cast<rwriteback_t>(exe(&issued));

    EXPECT_EQ(res->data[0], 0x3f800000);
}