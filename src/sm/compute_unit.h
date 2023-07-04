/*
 * Copyright © 2023 Sietium Semiconductor.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef RVGPU_CMODEL_CU_H
#define RVGPU_CMODEL_CU_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include "decoder.h"
#include "mmu.h"
#include "common/inst_constant.h"

class compute_unit;

typedef reg_t (*insn_func_t)(compute_unit *, insn_t, reg_t);

struct insn_fetch_t {
    insn_func_t func;
    insn_t insn;
};

struct insn_desc_t {
    insn_bits_t match;
    insn_bits_t mask;
    insn_func_t rv32i;

    [[nodiscard]] insn_func_t func() const {
        return rv32i;
    }

    static insn_desc_t illegal() {
        //fixme:should handle with the illegal instruction
        //return {0, 0, &illegal_instruction};
        return {0, 0};
    }
};

// architectural state of a RISC-V hart
struct state_t {
    void reset();

    reg_t pc;
    regfile_t<reg_t, NXPR, true> XPR;
    regfile_t<freg_t, NFPR, false> FPR;

    struct regext_t {
        regext_t() : ext_rd(0), ext_rs1(0), ext_rs2(0), ext_rs3(0), ext_imm(0), valid(0) {}
        uint64_t ext_rd, ext_rs1, ext_rs2, ext_rs3, ext_imm, valid;
    };

    regext_t regext_info;
    bool regext_enable;
};

class compute_unit {
public:
    compute_unit();

    insn_fetch_t load_insn(reg_t pc);
    insn_func_t decode_insn(insn_t insn);
    reg_t execute_insn(reg_t pc, insn_fetch_t fetch);

    [[nodiscard]] uint64_t ext_rd() const { return m_state.regext_info.valid ? (m_state.regext_info.ext_rd << 5) : 0; }
    uint64_t ext_rs1(){ return m_state.regext_info.valid ? (m_state.regext_info.ext_rs1<<5)  : 0;}
    state_t* get_state(){return &m_state;}

private:
    mmu_t *m_mmu;
    state_t m_state;

    std::vector<insn_desc_t> instructions{};
    static const size_t OPCODE_CACHE_SIZE = 8191;
    insn_desc_t opcode_cache[OPCODE_CACHE_SIZE]{};

    void register_insn(insn_desc_t);
    void register_base_instructions();
    void build_opcode_map();

    void ext_clear();
};

#endif //RVGPU_CMODEL_CU_H
