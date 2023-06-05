# mock a libdrm interface
set(LIBDRM_FILES libdrm_rvgpu.h libdrm_rvgpu.c)

include(FindPkgConfig)
pkg_check_modules(LIBDRM REQUIRED libdrm)

add_library(drm_rvgpu SHARED ${LIBDRM_FILES})
target_include_directories(drm_rvgpu PRIVATE ${LIBDRM_INCLUDE_DIRS})
set_target_properties(drm_rvgpu PROPERTIES VERSION 1)
set_target_properties(drm_rvgpu PROPERTIES LINK_FLAGS_RELEASE -s)

configure_file(
    libdrm_rvgpu.pc.in
    libdrm_rvgpu.pc
    @ONLY
)

install(TARGETS drm_rvgpu LIBRARY DESTINATION lib)
install(FILES libdrm_rvgpu.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libdrm_rvgpu.pc DESTINATION lib/pkgconfig)
