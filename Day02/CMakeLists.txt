# CMakeList.txt : CMake project for Day02, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (Day02 "Day02.cpp")

install (TARGETS Day02 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)