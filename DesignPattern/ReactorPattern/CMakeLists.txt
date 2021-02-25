# CMakeList.txt : CMake project for ReactorPattern, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ReactorPattern")

# Add source to this project's executable.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable (ReactorPattern "ReactorPattern.cpp" "ReactorPattern.h")

# TODO: Add tests and install targets if needed.
