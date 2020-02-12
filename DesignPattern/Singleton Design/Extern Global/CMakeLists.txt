# CMakeList.txt : CMake project for Singleton_Design, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Singleton_Design")

if(MSVC)
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_STANDARD 17)
endif(MSVC)

# Add source to this project's executable.
add_executable (Singleton_Design "src/MySingleton.cpp" "src/main.cpp" "src/UseSingleton.cpp")

# TODO: Add tests and install targets if needed.
