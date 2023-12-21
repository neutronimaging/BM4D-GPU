# ~~~
# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (c) 2021 ImaginSuite contributors (https://github.com/neutronimaging/imagingsuite)
# ~~~
set(TARGET_NAME "pybm4d")
project(bm4d LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}" VERSION_LESS "3.5")
  message(
    FATAL_ERROR
      "Python v3 interpreter must be greater than or equal to 3.5. Found ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}"
  )
endif()

include_directories(
  ../libbm4d/include
    )

set(SRC_FILES 
    src/bm4d.cpp
    src/pybinder.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /NODEFAULTLIB:LIBCMTD.lib")

set(LINK_TYPE "MODULE")

pybind11_add_module(${TARGET_NAME}
  ${LINK_TYPE}
  MODULE
  ${SRC_FILES}  
)

set_target_properties(${TARGET_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)




message("${TARGET_NAME} ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# set_target_properties(${TARGET} PROPERTIES 
#     POSITION_INDEPENDENT_CODE ON
#     CUDA_VISIBILITY_PRESET "hidden"
#     # CUDA_SEPARABLE_COMPILATION ON
# )

target_link_libraries(${TARGET_NAME}
  PUBLIC
    pybind11::module
    libbm4d
      )


set_target_properties(${TARGET_NAME}
  PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
  )

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/pybm4d)