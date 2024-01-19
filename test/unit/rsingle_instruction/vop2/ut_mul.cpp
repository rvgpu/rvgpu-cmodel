#include <gtest/gtest.h>
#include "rcore/rcore.hpp"
#include "simt/simt.hpp"
#include "inst.hpp"
#include "common/math.hpp"

TEST_F(inst, decode_v_mul_f32) {
    // v_mul_f32_e32 v1, v1, v2
    inst_init(0x10020501);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());

    EXPECT_EQ(res->type, VOP2);
    EXPECT_EQ(res->op, 8);
    EXPECT_EQ(res->src0_id, 257);
    EXPECT_EQ(res->src1_id, 2);
}

TEST_F(inst, exe_v_mul_f32) {
    rinst_issue issued{};
    issued.type = VOP2;
    issued.op = 8;
    issued.src0[0] = ftou(2.5);
    issued.src1[0] = ftou(3.46);

    auto res = dynamic_pointer_cast<rwriteback_t>(exe(&issued));
    EXPECT_EQ(res->data[0], ftou(2.5 * 3.46));
}