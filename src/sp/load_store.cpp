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

#include <cstdio>

#include "load_store.hpp"
#include "encoding.hpp"

load_store::load_store(register_file *regfile) {
    m_reg = regfile;
}

uint64_t load_store::run(inst_issue inst) {
    proc_inst = inst;
    uint64_t result = 0;

    switch (inst.code) {
        case encoding::INST_LS_SW: {
            uint64_t addr = inst.rs1 + inst.s_imm;
            printf("[EXEC.LS.SW] store.i32: mem[0x%lx] = 0x%lx\n", addr, inst.rs2);
            *((uint32_t *)addr) = (uint32_t)inst.rs2;
            break;
        }
        case encoding::INST_LS_SD: {
            uint64_t addr = inst.rs1 + inst.s_imm;
            uint64_t data = inst.rs2;
            printf("[EXEC.LS.SD] store.i64: mem[0x%lx] = 0x%lx\n", addr, data);
            *((uint64_t *)addr) = (uint64_t)data;
            break;
        }
        case encoding::INST_LS_LW: {
            uint64_t addr = inst.rs1 + inst.i_imm;
            uint32_t data = *((uint32_t *)addr);
            printf("[EXEC.LS.LW] load.i32: r[%ld] 0x%x from 0x%lx\n", inst.rd, data, addr);
            m_reg->write_ireg<uint32_t>(0, inst.rd, data);
            break;
        }
        case encoding::INST_LS_LD: {
            uint64_t addr = inst.rs1 + inst.i_imm;
            uint64_t data = *((uint64_t *)addr);
            printf("[EXEC.LS.LD] load.i64: r[%ld] 0x%lx from 0x%lx\n", inst.rd, data, addr);
            m_reg->write_ireg<uint64_t>(0, inst.rd, data);
            break;
        }
        default:
            printf("error code of load store\n");
            break;
    }

    return result;
}
