# CMakeList.txt : CMake project for Day06, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day06 "Day06.cpp")

install (TARGETS Day06 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)