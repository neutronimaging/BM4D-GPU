cmake_minimum_required(VERSION 2.8)
set(TARGET_NAME "bm4d-gpu")
project(bm4d-gpu)

## Add support for C++14
set(CMAKE_CXX_STANDARD 17)

find_package(CUDA REQUIRED)

include_directories(include)

set(CXX
        src/bm4d.cpp
        )

set(CU  src/kernels.cu)

set(H
        include/bm4d.h
        include/helper_cuda.h
        include/helper_string.h
        include/kernels.cuh
        include/parameters.h
        include/stopwatch.hpp
        include/utils.h
        )

# TODO: separate to lib/executable/gui
# TODO: add matlab/python bindings
cuda_add_library(${TARGET_NAME} SHARED 
        ${CXX} 
        ${CU} 
        ${H})
#target_link_libraries(bm4d-gpu ${OpenCV_LIBRARIES})
install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)