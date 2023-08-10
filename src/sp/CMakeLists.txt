set(SP_FILES
    register_file.hpp
    stream_processor.cpp
    stream_processor.hpp
    warp.cpp
    warp.hpp
    )

add_library(sp OBJECT ${SP_FILES})
