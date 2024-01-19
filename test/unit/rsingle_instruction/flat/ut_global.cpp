#include <gtest/gtest.h>
#include "rcore/rcore.hpp"
#include "simt/simt.hpp"
#include "inst.hpp"

TEST_F(inst, decode_global_load_b32) {
    // global_load_b32 v1, v0, s[4:5]
    inst_init(0xDC520000, 0x01040000);
    auto res = dynamic_pointer_cast<rinst_issue>(decode());

    EXPECT_EQ(res->type, FLAT);
    EXPECT_EQ(res->op, 20);
    EXPECT_EQ(res->src0_id, 0);
    EXPECT_EQ(res->src1_id, 4);
    EXPECT_EQ(res->dst_id, 1);
    EXPECT_EQ(res->offset, 0);
}

TEST_F(inst, exe_global_load_b32) {
    rinst_issue issue{};
    issue.type = FLAT;
    issue.op = 20;
    issue.src1[0] = 2; //offsest
    //base address is 0x123
    issue.src0[0] = 0x123;
    issue.src0[1] = 0;
    std::vector<uint32_t> data={1,2,3,0};
    uint64_t addr = 0x123 + 2;
    preload_data_to_vram(addr, data, 1);
    auto res = dynamic_pointer_cast<rwriteback_t>(exe(&issue));

    EXPECT_EQ(res->data_size, 1);
    EXPECT_EQ(res->data[0], 1);
}