# CMakeList.txt : CMake project for Day04, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day04 "Day04.cpp")

install (TARGETS Day04 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)