configure_file(
    ${PROJECT_SOURCE_DIR}/src/common/configs.h.in
    ${PROJECT_BINARY_DIR}/src/common/configs.h
)

set(UTILS_FILES
    utils.cpp
    type.hpp
)

add_library(utils OBJECT ${UTILS_FILES})