#include <gtest/gtest.h>
#include "simt/simt.hpp"
#include "inst.hpp"

TEST_F(inst, decode_load_b128) {
    //s_load_b128 s[4:7], s[0:1], 0x8  F4080100 F8000008
    inst_init(0xF4080100, 0xF8000008);
    auto res = dynamic_cast<rinst_issue*>(decode().get());

    EXPECT_EQ(res->op, 2);
    EXPECT_EQ(res->sbase, 0);
    EXPECT_EQ(res->sdata, 4);
    EXPECT_EQ(res->dlc, 0);
    EXPECT_EQ(res->glc, 0);
    EXPECT_EQ(res->offset, 8);
    EXPECT_EQ(res->soffset, 0x7c);
}

TEST_F(inst, exe_load_b128) {
    rinst_issue issue;
    issue.type = SMEM;
    issue.op = 2;
    issue.sbase = 0;
    issue.sdata = 4;
    issue.offset = 8;
    issue.soffset = 0x7c;
    //sbase = 0x123;
    issue.src0[0] = 0x123;
    issue.src0[1] = 0;
    //soffet = 2;
    issue.src1[0] = 2;

    std::vector<uint32_t> data={0,1,2,3};
    //addr = sbase + soffset + offset
    uint64_t addr = 0x123 + 2 + 8;
    preload_data_to_vram(addr, data, 4);
    auto res = static_pointer_cast<rwriteback_t>(exe(&issue));
    
    EXPECT_EQ(res->data[0], 0);
    EXPECT_EQ(res->data[1], 1);
    EXPECT_EQ(res->data[2], 2);
    EXPECT_EQ(res->data[3], 3);
}

TEST_F(inst, decode_load_b32) {
    // s_load_b32 s0, s[0:1], null  F4000000 F8000000
    inst_init(0xF4000000, 0xF8000000);
    auto res = std::dynamic_pointer_cast<rinst_issue>(decode());
    EXPECT_EQ(res->op, 0);
    EXPECT_EQ(res->dlc, 0);
    EXPECT_EQ(res->glc, 0);
    EXPECT_EQ(res->sdata, 0);
    EXPECT_EQ(res->sbase, 0);
    EXPECT_EQ(res->offset, 0);
    EXPECT_EQ(res->soffset, 0x7c);
}

TEST_F(inst, exe_load_b32) {
    rinst_issue issue;
    issue.type = SMEM;
    issue.op = 0;
    issue.sdata = 0;
    issue.sbase = 0;
    issue.offset = 0;
    issue.soffset = 0x7c;
    //sbase = 0x123;
    issue.src0[0] = 0x123;
    issue.src0[1] = 0;
    //soffet = 0;
    issue.src1[0] = 0;

    std::vector<uint32_t> data={1,2,3,0};
    //addr = sbase + soffset + offset
    uint64_t addr = 0x123 + 0 + 0;
    preload_data_to_vram(addr, data, 1);
    auto res = static_pointer_cast<rwriteback_t>(exe(&issue));

    EXPECT_EQ(res->data.size(), 1);
    EXPECT_EQ(res->data[0], 1);
}