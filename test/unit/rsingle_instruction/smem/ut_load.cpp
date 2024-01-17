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

    //auto res = exe(&issue);
    EXPECT_EQ(res->data[0], 0);
    EXPECT_EQ(res->data[1], 1);
    EXPECT_EQ(res->data[2], 2);
    EXPECT_EQ(res->data[3], 3);
}