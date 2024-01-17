#include <gtest/gtest.h>
#include "rcore/rcore.hpp"
#include "simt/simt.hpp"
#include "inst.hpp"

TEST_F(inst, decode_clause) {
    // s_clause 0x1
    inst_init(0xBF850001);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());

    EXPECT_EQ(res->op, 5);
    EXPECT_EQ(res->simm16, 1);
}