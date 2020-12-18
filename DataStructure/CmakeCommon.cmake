function(AddExecutableAndTest)
    set(options OPTIONAL)
    set(args NAME)
    set(list_args FILES)
    cmake_parse_arguments(
        PARSE_ARGV
        0
        var
        ${options}
        ${args}
        ${list_args}
    )
    message("Adding Test: ${var_NAME}")
    message("\tfrom files:")
    foreach(item IN LISTS var_FILES)
        message("\t\t${item}")
    endforeach()
    add_executable(${var_NAME} ${var_FILES})
    gtest_add_tests(
        TARGET ${var_NAME}
    )
    target_link_libraries(${var_NAME} PRIVATE ${GtestLibs})
endfunction()