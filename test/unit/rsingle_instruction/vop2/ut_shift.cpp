#include <gtest/gtest.h>
#include "rcore/rcore.hpp"
#include "simt/simt.hpp"
#include "inst.hpp"

TEST_F(inst, decode_lshlrev_b32) {
    // v_lshlrev_b32_e32 v0, 2, v0
    inst_init(0x30000082);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());

    EXPECT_EQ(res->type, VOP2);
    EXPECT_EQ(res->op, 24);
    EXPECT_EQ(res->src0_id, 130);
    EXPECT_EQ(res->src1_id, 0);
    EXPECT_EQ(res->dst_id, 0);
}

TEST_F(inst, exe_lshlrev_b32) {
    rinst_issue issued{};
    issued.type = VOP2;
    issued.op = 24;
    // 第130号标量寄存器是一个常量寄存器，值为2
    issued.src0[0] = 2;
    issued.src1[0] = 1;

    auto res = dynamic_pointer_cast<rwriteback_t>(exe(&issued));

    EXPECT_EQ(res->data[0], 1 << 2);
}
