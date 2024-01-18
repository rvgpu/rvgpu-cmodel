#ifndef RVGSIM_INST_TYPE_HPP
#define RVGSIM_INST_TYPE_HPP

#include <cstdint>
#include <vector>
#include "common/type.hpp"

enum rinst_type {
    UNKNOWN,
    SOPP,
    SMEM,
    VOP1
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
};

#define SOPP_MASK 0xff800000
#define SOPP_MATCH 0xbf800000
#define SMEM_MASK 0xfc000000
#define SMEM_MATCH 0Xf4000000

#define VOP1_MASK 0xfe000000
#define VOP1_MATCH 0x7e000000

#endif //RVGSIM_INST_TYPE_HPP
