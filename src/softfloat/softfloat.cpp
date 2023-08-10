#include "softfloat.hpp"

enum {
    softfloat_flag_inexact   =  1,
    softfloat_flag_underflow =  2,
    softfloat_flag_overflow  =  4,
    softfloat_flag_infinite  =  8,
    softfloat_flag_invalid   = 16
};

#define signF32UI( a ) ((bool) ((uint32_t) (a)>>31))
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))

uint_fast8_t softfloat_exceptionFlags = 0;

void softfloat_raiseFlags( uint_fast8_t flags )
{
    softfloat_exceptionFlags |= flags;
}

bool f32_le(uint32_t a, uint32_t b)
{
    uint_fast32_t uiA;
    uint_fast32_t uiB;
    bool signA, signB;

    uiA = a;
    uiB = b;
    if ( isNaNF32UI( uiA ) || isNaNF32UI( uiB ) ) {
        softfloat_raiseFlags( softfloat_flag_invalid );
        return false;
    }
    signA = signF32UI( uiA );
    signB = signF32UI( uiB );
    return
        (signA != signB) ? signA || ! (uint32_t) ((uiA | uiB)<<1)
            : (uiA == uiB) || (signA ^ (uiA < uiB));
}