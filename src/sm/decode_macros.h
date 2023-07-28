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

#define READ_FREG(reg) STATE.FPR[reg]

#define READ_FREG_F(reg) f32(READ_FREG(reg))
#define READ_FREG_D(reg) f64(READ_FREG(reg))

#define FRS1 READ_FREG(insn.rs1())
#define FRS2 READ_FREG(insn.rs2())
#define FRS3 READ_FREG(insn.rs3())
#define FRS1_F READ_FREG_F(insn.rs1())
#define FRS1_D READ_FREG_D(insn.rs1())
#define FRS2_F READ_FREG_F(insn.rs2())
#define FRS2_D READ_FREG_D(insn.rs2())

#define WRITE_FREG(reg, value) do { \
    freg_t wdata = freg(value); \
    STATE.FPR.write(reg, wdata); \
  } while(0)

#define WRITE_FRD(value) WRITE_FREG(insn.rd(), value)

#define WRITE_FRD_F(value) WRITE_FRD(value)
#define WRITE_FRD_D(value) WRITE_FRD(value)

inline float16_t f16(uint16_t v) { return { v }; }
inline float32_t f32(uint32_t v) { return { v }; }
inline float64_t f64(uint64_t v) { return { v }; }
inline float16_t f16(freg_t r) { return f16((uint16_t)r.v[0]); }
inline float32_t f32(freg_t r) { return f32((uint32_t)r.v[0]); }
inline float64_t f64(freg_t r) { return f64(r.v[0]); }
inline float128_t f128(freg_t r) { return r; }

inline freg_t freg(float16_t f) { return { ((uint64_t)-1 << 16) | f.v, (uint64_t)-1 }; }
inline freg_t freg(float32_t f) { return { ((uint64_t)-1 << 32) | f.v, (uint64_t)-1 }; }
inline freg_t freg(float64_t f) { return { f.v, (uint64_t)-1 }; }
inline freg_t freg(float128_t f) { return f; }

#endif //RVGSIM_DECODE_MACROS_H
