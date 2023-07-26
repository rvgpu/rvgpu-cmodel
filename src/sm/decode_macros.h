#ifndef RVGSIM_DECODE_MACROS_H
#define RVGSIM_DECODE_MACROS_H

#define MMU (*p->get_mmu())
#define RS2 READ_REG(insn.rs2())
#define SHAMT (insn.i_imm() & 0x3F)

#define require_rv64 require(xlen == 64)
#define require_either_extension(A,B) require(p->extension_enabled(A) || p->extension_enabled(B));
#define sext32(x) ((sreg_t)(int32_t)(x))

#define set_pc(x) \
        do { p->check_pc_alignment(x); \
             npc = sext_xlen(x);       \
           } while (0)
#endif //RVGSIM_DECODE_MACROS_H
