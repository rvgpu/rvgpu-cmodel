set(SP_FILES
    alu.cpp
    alu.hpp
    decoder.cpp
    decoder.hpp
    flu.cpp
    flu.hpp
    load_store.cpp
    load_store.hpp
    register_file.hpp
    stream_processor.cpp
    stream_processor.hpp
    warp.cpp
    warp.hpp
    )

add_library(sp OBJECT ${SP_FILES})
