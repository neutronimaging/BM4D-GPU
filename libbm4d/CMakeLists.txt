
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
set(TARGET_NAME "libbm4d")
project(bm4d LANGUAGES CXX CUDA)

include(CTest)

set(CXX
        src/bm4d.cpp
        src/bm4d_core.cpp
        )

set(CU  
        src/kernels.cu
        )

set(H
        include/bm4d.h
        include/bm4d_core.h
        include/helper_cuda.h
        include/helper_string.h
        include/kernels.cuh
        include/parameters.h
        include/stopwatch.hpp
        include/utils.h
        )

add_library(${TARGET_NAME} SHARED
        ${CXX} 
        ${CU} 
        ${H}
  )

# Request that particles be built with -std=c++11
# As this is a public compile feature anything that links to particles
# will also build with -std=c++11
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_11)

# We need to explicitly state that we need all CUDA files in the particle
# library to be built with -dc as the member functions could be called by
# other libraries and executables

target_compile_definitions(${TARGET_NAME} PRIVATE BM4D_LIBRARY)
set_target_properties( ${TARGET_NAME}
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON
                      )



install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/pybm4d)