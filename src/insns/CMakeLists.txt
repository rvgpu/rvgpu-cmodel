macro(add_instruction instname)
    add_custom_command(
        OUTPUT ${instname}.cpp
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate_inst.py ${CMAKE_CURRENT_SOURCE_DIR} ${instname}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_inst.py
    )

    list(APPEND inst_source_list ${instname}.cpp)
endmacro()

add_instruction(addi)
add_instruction(auipc)
add_instruction(lui)

add_library(insns STATIC ${inst_source_list})
target_include_directories(insns PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
