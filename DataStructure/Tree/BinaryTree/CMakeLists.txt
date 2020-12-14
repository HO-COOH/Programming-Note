add_executable(BinaryTree main.cpp)
target_link_libraries(BinaryTree PRIVATE ${GtestLibs})
gtest_add_tests(
    TARGET BinaryTree
)