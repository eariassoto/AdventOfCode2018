# CMakeList.txt : CMake project for Day07, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day07 "Day07.cpp")

install (TARGETS Day07 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)