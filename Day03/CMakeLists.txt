# CMakeList.txt : CMake project for Day03, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day03 "Day03.cpp")

install (TARGETS Day03 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)