#pragma once

typedef int64_t sreg_t;
typedef uint64_t reg_t;

#define sext32(x)       ((sreg_t)(int32_t)(x))
#define zext32(x)       ((reg_t)(uint32_t)(x))
#define sext_64(x)      (((sreg_t)(x) << (64 - 64)) >> (64 - 64))
#define sext_32(x)      (((sreg_t)(x) << (64 - 32)) >> (64 - 32))
#define zext(x, pos)    (((reg_t)(x) << (64 - (pos))) >> (64 - (pos)))
#define zext_64(x)      zext(x, 64)
#define sext_xlen(x)    (((sreg_t)(x) << (64 - 64)) >> (64 - 64))
#define zext_xlen(x)    zext(x, 64)
#define SHAMT           (inst.i_imm & 0x3F)

#define F32_SIGN ((uint32_t)1 << 31)
#define F64_SIGN ((uint64_t)1 << 63)