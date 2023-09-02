function(rvsim_test_draw target testname)
    add_executable(${target} ${testname})
    target_link_libraries(${target} rvgsim gtest gtest_main)
    target_link_libraries(${target} ${opencv_lib_LIBRARIES})
    target_include_directories(${target} PRIVATE ${opencv_lib_INCLUDE_DIRS})
    target_include_directories(${target} PRIVATE ${project_top_path}/src)
    target_include_directories(${target} PRIVATE ${project_top_path}/test/draw)
    target_include_directories(${target} PRIVATE ${PROJECT_BINARY_DIR}/src)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

<<<<<<< HEAD
find_package(PkgConfig)
pkg_search_module(opencv_lib REQUIRED opencv4)

set(DEVICE_C_FLAGS -xc -march=rv64imafd -mcmodel=medany -lm -e gpumain -nostartfiles -static -fno-PIC)
set(DEVICE_CPP_FLAGS -xc++ -march=rv64imafd -mcmodel=medany -lm -e gpumain -nostartfiles -static -fno-PIC)

function(rvgpu_cxx target)
=======
set(DEVICE_C_FLAGS -xc -march=rv64imafd -mcmodel=medany -lm -nostartfiles -static -fno-PIC)
set(DEVICE_CPP_FLAGS -xc++ -march=rv64imafd -mcmodel=medany -lm -nostartfiles -static -fno-PIC)
function(rvgpu_cxx target mainfunc)
>>>>>>> 9acaa61 (fix: build device function use a custom funcname)
    message("Generate ${CMAKE_CURRENT_BINARY_DIR}/${target}")
    execute_process(COMMAND riscv64-linux-gnu-g++ ${DEVICE_CPP_FLAGS} -e ${mainfunc} ${CMAKE_CURRENT_SOURCE_DIR}/${target}.hpp -o ${CMAKE_CURRENT_BINARY_DIR}/${target})
endfunction()
<<<<<<< HEAD

function(rvgpu_cc target)
=======
function(rvgpu_cc target mainfunc)
>>>>>>> 9acaa61 (fix: build device function use a custom funcname)
    message("Generate ${CMAKE_CURRENT_BINARY_DIR}/${target}")
    execute_process(COMMAND riscv64-linux-gnu-gcc ${DEVICE_C_FLAGS} -e ${mainfunc} ${CMAKE_CURRENT_SOURCE_DIR}/${target}.h -o ${CMAKE_CURRENT_BINARY_DIR}/${target})
endfunction()


add_subdirectory(basic)
add_subdirectory(games101)