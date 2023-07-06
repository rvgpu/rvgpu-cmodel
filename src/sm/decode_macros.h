#ifndef RVGSIM_DECODE_MACROS_H
#define RVGSIM_DECODE_MACROS_H

#define MMU (*p->get_mmu())
#define RS2 READ_REG(insn.rs2())
#define SHAMT (insn.i_imm() & 0x3F)

#define require_rv64 require(xlen == 64)
#define sext32(x) ((sreg_t)(int32_t)(x))
#endif //RVGSIM_DECODE_MACROS_H
