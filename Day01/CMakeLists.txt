# CMakeList.txt : CMake project for Day01, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day01 "Day01.cpp")

install (TARGETS Day01 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)