//
// Created by max on 23-4-27.
//

#ifndef RVGSIM_SOFTFLOAT_TYPES_H
#define RVGSIM_SOFTFLOAT_TYPES_H

#include <cstdint>

/*----------------------------------------------------------------------------
| Types used to pass 16-bit, 32-bit, 64-bit, and 128-bit floating-point
| arguments and results to/from functions.  These types must be exactly
| 16 bits, 32 bits, 64 bits, and 128 bits in size, respectively.  Where a
| platform has "native" support for IEEE-Standard floating-point formats,
| the types below may, if desired, be defined as aliases for the native types
| (typically 'float' and 'double', and possibly 'long double').
*----------------------------------------------------------------------------*/
typedef struct { uint16_t v; } float16_t;
typedef struct { uint32_t v; } float32_t;
typedef struct { uint64_t v; } float64_t;
typedef struct { uint64_t v[2]; } float128_t;

float32_t f32_mul(float32_t a, float32_t b);
float64_t f64_mul(float64_t a, float64_t b);

#endif //RVGSIM_SOFTFLOAT_TYPES_H
