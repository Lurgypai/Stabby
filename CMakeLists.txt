﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_USER_MAKE_RULES_OVERRIDE
  ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
  ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides.cmake)


project ("StabbyOrganized")

# Include sub-projects.
add_subdirectory ("Suqua")
add_subdirectory ("StabbyCore")
add_subdirectory ("Stabby")
add_subdirectory ("StabbyServer")
add_subdirectory ("enet-master")
# add_subdirectory ("Tests/HRTag")
# add_subdirectory ("Tests/CharBuffer")
