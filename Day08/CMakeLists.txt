# CMakeList.txt : CMake project for Day08, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day08 "Day08.cpp")

install (TARGETS Day08 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)