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

#include <cassert>
#include "common/inst_constant.h"
#include "common/command_stream.h"
#include "compute_unit.h"

insn_fetch_t compute_unit::load_insn(reg_t pc) {
    auto insn = (insn_bits_t) (m_mmu->load<uint32_t>(pc));
    return insn_fetch_t{decode_insn(insn_t(insn)), insn_t(insn)};
}

insn_func_t compute_unit::decode_insn(insn_t insn) {
    // look up opcode in hash table
    size_t idx = insn.bits() % OPCODE_CACHE_SIZE;
    insn_desc_t desc = opcode_cache[idx];

    if (insn.bits() != desc.match) {
        // fall back to linear search
        int cnt = 0;
        insn_desc_t *p = &instructions[0];
        while ((insn.bits() & p->mask) != p->match)
            p++, cnt++;
        desc = *p;

        if (p->mask != 0 && p > &instructions[0]) {
            if (p->match != (p - 1)->match && p->match != (p + 1)->match) {
                // move to front of opcode list to reduce miss penalty
                while (--p >= &instructions[0])
                    *(p + 1) = *p;
                instructions[0] = desc;
            }
        }
        opcode_cache[idx] = desc;
        opcode_cache[idx].match = insn.bits();
    }
    return desc.func(m_xlen);
}

compute_unit::compute_unit() {
    m_isa = new isa_parser_t("RV32I");
    m_xlen = 32;
    m_mmu = new mmu_t();
    register_base_instructions();
    m_state.reset();
}

void compute_unit::register_base_instructions() {
#define DECLARE_INSN(name, match, mask) \
    insn_bits_t name##_match = (match), name##_mask = (mask); \
    bool name##_supported = true;

#include "insns/encoding.h"

#undef DECLARE_INSN

#define DEFINE_INSN(name) \
    extern reg_t fast_rv32i_##name(compute_unit*, insn_t, reg_t); \
    extern reg_t fast_rv64i_##name(compute_unit*, insn_t, reg_t);  \
    if (name##_supported) { \
      register_insn((insn_desc_t) { \
        name##_match, \
        name##_mask, \
        fast_rv32i_##name, \
        fast_rv64i_##name}); \
    }

#include "insns/insn_list.h"
#undef DEFINE_INSN

    build_opcode_map();
}

void compute_unit::init_register(uint32_t regn, reg_t data) {
    m_state.XPR.write(regn, data);
}

void compute_unit::register_insn(insn_desc_t desc) {
    assert(desc.rv64i);
    instructions.push_back(desc);
}

void compute_unit::build_opcode_map() {
    struct cmp {
        bool operator()(const insn_desc_t &lhs, const insn_desc_t &rhs) {
            if (lhs.match == rhs.match)
                return lhs.mask > rhs.mask;
            return lhs.match > rhs.match;
        }
    };
    std::sort(instructions.begin(), instructions.end(), cmp());

    for (auto &i: opcode_cache)
        i = insn_desc_t::illegal();
}

reg_t compute_unit::execute_insn(reg_t pc, insn_fetch_t fetch) {
    reg_t npc = fetch.func(this, fetch.insn, pc);
    if(m_state.regext_enable) {
        m_state.regext_enable = false;
    }else {
        ext_clear();
    }

    return npc;
}

void compute_unit::ext_clear() {
    m_state.regext_info.valid = 0;
    m_state.regext_info.ext_imm = 0;
    m_state.regext_info.ext_rd = 0;
    m_state.regext_info.ext_rs1 = 0;
    m_state.regext_info.ext_rs2 = 0;
    m_state.regext_info.ext_rs3 = 0;
}

compute_unit::compute_unit(const isa_parser_t *isa) {
    m_isa = isa;
    m_xlen = isa->get_max_xlen();
    m_mmu = new mmu_t();
    register_base_instructions();
    m_state.reset();
}

void state_t::reset() {
    pc = DEFAULT_RSTVEC;
    XPR.reset();
    FPR.reset();
    regext_info.ext_imm = 0;
    regext_info.valid = 0;
    regext_info.ext_rd = 0;
    regext_info.ext_rs1 = 0;
    regext_info.ext_rs2 = 0;
    regext_info.ext_rs3 = 0;
    regext_enable = false;
}
