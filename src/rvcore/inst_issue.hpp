#pragma once

#include <cstdint>
#include "rvmacro.h"
#include "common/regid.hpp"
#include "common/type.hpp"

struct rvinst_issue : inst_issue{
    uint32_t code;
    uint32_t type;
    int64_t jpc;

    uint64_t rs1_id;
    uint64_t rs2_id;
    uint64_t rs3_id;
    uint64_t frs1_id;
    uint64_t frs2_id;
    uint64_t frs3_id;
    special_reg sreg_id;

    uint64_t rd;
    uint64_t frd;
    uint64_t rs1;
    uint64_t rs2;
    uint64_t rs3;
    uint64_t frs1;
    uint64_t frs2;
    uint64_t frs3;
    reg_t sreg;

    int64_t u_imm;
    int64_t i_imm;
    int64_t s_imm;
    int64_t sb_imm;
    int64_t uj_imm;
    uint64_t rm;
} ;
