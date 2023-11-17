cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(bm4d-gpu)

## Add support for C++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenMP)
find_package(PythonInterp REQUIRED)
find_package(pybind11 REQUIRED)
find_package(CUDA REQUIRED)

if(WIN32)
add_compile_options(
  /openmp 
  /O2
  )
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
  add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wunused
    -Wshadow
    -Winit-self
    -Wpointer-arith
    -Woverloaded-virtual
    -Wold-style-cast
    -Wcast-qual
    -Wcast-align
  )
  add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-operator-names>
  )
endif()


add_subdirectory(libbm4d)
add_subdirectory(pybm4d)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/applications)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


