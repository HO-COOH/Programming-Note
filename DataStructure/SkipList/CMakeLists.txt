# CMakeList.txt : CMake project for SkipList, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project ("SkipList")

# Add source to this project's executable.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../GTest/)

add_executable (SkipList "SkipList.cpp" "SkipList.h")
target_compile_features(SkipList PUBLIC cxx_std_17)

message(${CMAKE_BUILD_TYPE})

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	target_link_libraries(SkipList ${CMAKE_CURRENT_SOURCE_DIR}/../GTest/gtestd.lib)
	message(debug build)
else()
	target_link_libraries(SkipList ${CMAKE_CURRENT_SOURCE_DIR}/../GTest/gtest.lib)
	message(release build)
endif()

# TODO: Add tests and install targets if needed.
