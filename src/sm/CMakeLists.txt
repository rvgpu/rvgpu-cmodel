set(SM_FILES
        compute_unit.h
        compute_unit.cpp
        decoder.h
        decode_macros.h
        mmu.h
        isa_parser.h)

add_library(sm OBJECT ${SM_FILES})
