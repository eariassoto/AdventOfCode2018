# CMakeList.txt : CMake project for Day05, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day05 "Day05.cpp")

install (TARGETS Day05 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)