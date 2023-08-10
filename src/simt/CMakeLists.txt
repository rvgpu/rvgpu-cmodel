set(SIMT_FILES
    register_file.hpp
    simt.cpp
    simt.hpp
    warp.cpp
    warp.hpp
    )

add_library(simt OBJECT ${SIMT_FILES})
