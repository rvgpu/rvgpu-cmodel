
# mock a libdrm interface
set(LIBDRM_FILES libdrm.c)

include(FindPkgConfig)
pkg_check_modules(LIBDRM REQUIRED libdrm)

add_library(drm SHARED ${LIBDRM_FILES})
target_include_directories(drm PRIVATE ${LIBDRM_INCLUDE_DIRS})
set_target_properties(drm PROPERTIES VERSION 2)
set_target_properties(drm PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS drm LIBRARY DESTINATION lib)
