macro(add_instruction instname)
    add_custom_command(
        OUTPUT ${instname}.cpp
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate_inst.py ${CMAKE_CURRENT_SOURCE_DIR} ${instname}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_inst.py
    )

    list(APPEND inst_list ${instname})
endmacro()

include(instructions.cmake)

# Generate insn_list.h and append to source list
FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/insn_list.h "")
foreach(iname ${inst_list})
    FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/insn_list.h "DEFINE_INSN(${iname})\n")
    list(APPEND inst_source_list ${iname}.cpp)
endforeach()
list(APPEND list_source_list insn_list.h)

add_library(insns OBJECT ${inst_source_list})
target_include_directories(insns PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
