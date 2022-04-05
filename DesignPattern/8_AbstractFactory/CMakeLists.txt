include_directories(include)

file(GLOB Sources src/*.cpp)

add_executable(AbstractFactory  ${Sources})