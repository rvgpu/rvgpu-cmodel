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

#ifndef RVGSIM_RCORE_HPP
#define RVGSIM_RCORE_HPP

#include "simt/core.hpp"
#include "inst_type.hpp"
#include "vram/vram.hpp"
#include "mmu/mmu.hpp"
#include "common/configs.h"

class simt;
#define REG_SIZE 256

class rcore : public mcore{
public:
    rcore(simt *simt_processor,vram *rgpu_vram, mmu *rgpu_mmu);
    void register_setup(message msg) override {};
    std::unique_ptr<inst_issue> decode(uint32_t inst_code) override;
    void get_operand(uint32_t tid, inst_issue* to_issue) override;
    std::unique_ptr<writeback_t> exe(inst_issue* to_issue, uint32_t tid) override;
    void write_back(uint32_t tid, writeback_t* data) override;

    std::vector<uint32_t> load(uint64_t addr, uint32_t data_size);
private:
    simt* m_simt;
    //scalar register
    uint32_t s_reg[SP_WARP_N][REG_SIZE]{};
    //vector register
    uint32_t v_reg[SP_WARP_N][REG_SIZE]{};

    vram *m_vram;
    mmu  *m_mmu;

    std::unique_ptr<writeback_t> exe_smem(rinst_issue* issued);
    std::unique_ptr<writeback_t> exe_vop1(rinst_issue* issued);

    uint32_t read_sreg(uint32_t tid, uint32_t reg_id);
    uint32_t read_vreg(uint32_t tid, uint32_t reg_id);
    void write_sreg(uint32_t wid, uint32_t reg_id, uint32_t data);
    void write_vreg(uint32_t wid, uint32_t reg_id, uint32_t data);
};


#endif //RVGSIM_RCORE_HPP
