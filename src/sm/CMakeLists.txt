set(SM_FILES
        compute_unit.h
        compute_unit.cpp
        decoder.h
        decode_macros.h
        mmu.h
        isa_parser.h
        stream_multiprocessor.h
        stream_multiprocessor.cpp
        f32_mul.cpp)

add_library(sm OBJECT ${SM_FILES})
