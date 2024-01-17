#include <gtest/gtest.h>
#include "rcore/rcore.hpp"
#include "simt/simt.hpp"
#include "inst.hpp"

TEST_F(inst, decode_clause) {
    // s_clause 0x1
    inst_init(0xBF850001);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());

    EXPECT_EQ(res->type, SOPP);
    EXPECT_EQ(res->op, 5);
    EXPECT_EQ(res->simm16, 1);
}

TEST_F(inst, decode_waitcnt) {
    //s_waitcnt lgkmcnt(0)   BF89FC07
    inst_init(0xBF89FC07);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());
    EXPECT_EQ(res->type, SOPP);
    EXPECT_EQ(res->op, 9);
    EXPECT_EQ(res->simm16, 0xfc07);
}