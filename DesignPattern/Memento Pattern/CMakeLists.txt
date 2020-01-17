# CMakeList.txt : CMake project for Memento Pattern, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Memento Pattern")

# Add source to this project's executable.

add_executable (CMakeTarget "MementoPattern.cpp" "main.cpp")
target_compile_features(CMakeTarget PUBLIC cxx_std_17)

# TODO: Add tests and install targets if needed.
