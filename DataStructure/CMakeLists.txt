cmake_minimum_required(VERSION 3.10)

project(DataStructure)

find_package(GTest CONFIG REQUIRED)
set(GtestLibs GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
enable_testing()
include(GoogleTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(CmakeCommon.cmake)

#add public include for all targets
include_directories(include)

#add all the subdirectories, which contains the target
add_subdirectory(LinearList)
#add_subdirectory(Tree)