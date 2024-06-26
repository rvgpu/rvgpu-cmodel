#pragma once

#define FRID(x)  (x + 32)

enum class reg {
    // General Registers: x0 ~ x31 (0 ~ 31)
    x0   = 0,   zero = 0,
    x1   = 1,   ra   = 1,
    x2   = 2,   sp   = 2,
    x3   = 3,   gp   = 3,
    x4   = 4,   tp   = 4,
    x5   = 5,   t0   = 5,
    x6   = 6,   t1   = 6,
    x7   = 7,   t2   = 7,
    x8   = 8,   s0   = 8,   fp   = 8,
    x9   = 9,   s1   = 9,
    x10  = 10,  a0   = 10,
    x11  = 11,  a1   = 11,
    x12  = 12,  a2   = 12,
    x13  = 13,  a3   = 13,
    x14  = 14,  a4   = 14,
    x15  = 15,  a5   = 15,
    x16  = 16,  a6   = 16,
    x17  = 17,  a7   = 17,
    x18  = 18,  s2   = 18,
    x19  = 19,  s3   = 19,
    x20  = 20,  s4   = 20,
    x21  = 21,  s5   = 21,
    x22  = 22,  s6   = 22,
    x23  = 23,  s7   = 23,
    x24  = 24,  s8   = 24,
    x25  = 25,  s9   = 25,
    x26  = 26,  s10  = 26,
    x27  = 27,  s11  = 27,
    x28  = 28,  t3   = 28,
    x29  = 29,  t4   = 29,
    x30  = 30,  t5   = 30,
    x31  = 31,  t6   = 31,
    // Float Registers: f0 ~ f31 (31 ~ 63)
    f0 = FRID(0),     ft0 = FRID(0),
    f1 = FRID(1),     ft1 = FRID(1),
    f2 = FRID(2),     ft2 = FRID(2),
    f3 = FRID(3),     ft3 = FRID(3),
    f4 = FRID(4),     ft4 = FRID(4),
    f5 = FRID(5),     ft5 = FRID(5),
    f6 = FRID(6),     ft6 = FRID(6),
    f7 = FRID(7),     ft7 = FRID(7),
    f8 = FRID(8),     fs0 = FRID(8),
    f9 = FRID(9),     fs1 = FRID(9),
    f10 = FRID(10),   fa0 = FRID(10),
    f11 = FRID(11),   fa1 = FRID(11),
    f12 = FRID(12),   fa2 = FRID(12),
    f13 = FRID(13),   fa3 = FRID(13),
    f14 = FRID(14),   fa4 = FRID(14),
    f15 = FRID(15),   fa5 = FRID(15),
    f16 = FRID(16),   fa6 = FRID(16),
    f17 = FRID(17),   fa7 = FRID(17),
    f18 = FRID(18),   fs2 = FRID(18),
    f19 = FRID(19),   fs3 = FRID(19),
    f20 = FRID(20),   fs4 = FRID(20),
    f21 = FRID(21),   fs5 = FRID(21),
    f22 = FRID(22),   fs6 = FRID(22),
    f23 = FRID(23),   fs7 = FRID(23),
    f24 = FRID(24),   fs8 = FRID(24),
    f25 = FRID(25),   fs9 = FRID(25),
    f26 = FRID(26),   fs10 = FRID(26),
    f27 = FRID(27),   fs11 = FRID(27),
    f28 = FRID(28),   ft8 = FRID(28),
    f29 = FRID(29),   ft9 = FRID(29),
    f30 = FRID(30),   ft10 = FRID(30),
    f31 = FRID(31),   ft11 = FRID(31),
    // PC Register: 64
    pc  = 64,
    // non register
    non = 65,
};

enum class fpreg {
    f0 = FRID(0),     ft0 = FRID(0),
    f1 = FRID(1),     ft1 = FRID(1),
    f2 = FRID(2),     ft2 = FRID(2),
    f3 = FRID(3),     ft3 = FRID(3),
    f4 = FRID(4),     ft4 = FRID(4),
    f5 = FRID(5),     ft5 = FRID(5),
    f6 = FRID(6),     ft6 = FRID(6),
    f7 = FRID(7),     ft7 = FRID(7),
    f8 = FRID(8),     fs0 = FRID(8),
    f9 = FRID(9),     fs1 = FRID(9),
    f10 = FRID(10),   fa0 = FRID(10),
    f11 = FRID(11),   fa1 = FRID(11),
    f12 = FRID(12),   fa2 = FRID(12),
    f13 = FRID(13),   fa3 = FRID(13),
    f14 = FRID(14),   fa4 = FRID(14),
    f15 = FRID(15),   fa5 = FRID(15),
    f16 = FRID(16),   fa6 = FRID(16),
    f17 = FRID(17),   fa7 = FRID(17),
    f18 = FRID(18),   fs2 = FRID(18),
    f19 = FRID(19),   fs3 = FRID(19),
    f20 = FRID(20),   fs4 = FRID(20),
    f21 = FRID(21),   fs5 = FRID(21),
    f22 = FRID(22),   fs6 = FRID(22),
    f23 = FRID(23),   fs7 = FRID(23),
    f24 = FRID(24),   fs8 = FRID(24),
    f25 = FRID(25),   fs9 = FRID(25),
    f26 = FRID(26),   fs10 = FRID(26),
    f27 = FRID(27),   fs11 = FRID(27),
    f28 = FRID(28),   ft8 = FRID(28),
    f29 = FRID(29),   ft9 = FRID(29),
    f30 = FRID(30),   ft10 = FRID(30),
    f31 = FRID(31),   ft11 = FRID(31),
};

//same with cuda
enum class special_reg {
    t0 = 0,     // tid.x
    t1,         // tid.y
    t2,         // tid.z
    t3,         // ntid.x
    t4,         // ntid.y
    t5,         // ntid.z
    t6,         // laneid
    t7,         // warpid
    t8,         // nwarpid
    t9,         // ctaid.x
    t10,        // ctaid.y
    t11,        // ctaid.z
    t12,        // simd
    t13         // nsimd
};