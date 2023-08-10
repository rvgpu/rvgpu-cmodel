set(RVCORE_FILES
    alu.cpp
    alu.hpp
    decoder.cpp
    decoder.hpp
    fpu.cpp
    fpu.hpp
    load_store.cpp
    load_store.hpp
    branch.cpp
    branch.hpp
    )

add_library(rvcore OBJECT ${RVCORE_FILES})
