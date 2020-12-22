cmake_minimum_required(VERSION 3.15)

project(LearnOpenGL)

find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)



set(Source ./src)
file(GLOB Sources "${Source}/*.cpp")

add_executable(Main
    ${Sources}
)
foreach(file ${Sources})
    message(${file})
endforeach()
target_link_libraries(Main PRIVATE GLEW::GLEW imgui::imgui)