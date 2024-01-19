#ifndef RVGSIM_INST_TYPE_HPP
#define RVGSIM_INST_TYPE_HPP

#include <cstdint>
#include <vector>
#include "common/type.hpp"

enum rinst_type {
    UNKNOWN,
    SOPP,
    SMEM,
    VOP1,
    VOP2,
    FLAT
};

struct rwriteback_t : writeback_t {
    bool vreg;
    uint32_t data_size;
    std::vector<uint32_t> data;
};

struct rinst_issue : inst_issue {
    uint32_t op;
    uint32_t src0[4];
    uint32_t src1[4];

    uint8_t dst_id;
    uint16_t src0_id;
    uint16_t src1_id;

    rinst_type type;
    //sopp
    uint16_t simm16;
    //smem
    uint8_t sbase;
    uint16_t sdata;
    bool     dlc;
    bool     glc;
    uint32_t offset;
    uint8_t soffset;
    //flat
    // --offset, use the one in smem
    // --dlc, use the one in smem
    // --glc, use the one in smem
    // --data, use the sdata in smem
    // --addr is src0;
    // --saddr is src1;
    bool slc;
    uint8_t seg;
    bool sve;
};

#define SOPP_MASK 0xff800000
#define SOPP_MATCH 0xbf800000
#define SMEM_MASK 0xfc000000
#define SMEM_MATCH 0Xf4000000

#define VOP1_MASK 0xfe000000
#define VOP1_MATCH 0x7e000000
#define VOP2_MASK 0x80000000
#define VOP2_MATCH 0x0

#define FLAT_MASK 0xfc000000
#define FLAT_MATCH 0xdc000000

#endif //RVGSIM_INST_TYPE_HPP
