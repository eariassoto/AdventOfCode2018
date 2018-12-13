# CMakeList.txt : CMake project for Day09, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day09 "Day09.cpp")

install (TARGETS Day09 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)