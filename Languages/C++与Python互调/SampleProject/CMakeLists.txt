cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakePythonTest")

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)
set (PYBIND11_PYTHON_VERSION "3.12.11")

#编译一个叫MyModule1的模块给Python调用
pybind11_add_module(MyModule1 MyModule1.cpp)
install(TARGETS MyModule1 DESTINATION .)

#用于将修改C++运行时库为静态链接
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

#用于给Release模式加pdb
#add_compile_options("$<$<NOT:$<CONFIG:Debug>>:/Zi>")
#add_link_options("$<$<NOT:$<CONFIG:Debug>>:/DEBUG>")
#add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
#add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")

#编译一个调用Python的C++程序
add_executable(example main.cpp)
target_link_libraries(example PRIVATE pybind11::embed)