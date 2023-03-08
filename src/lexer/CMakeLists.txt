cmake_minimum_required(VERSION 3.5)
project(Lexer VERSION 1.0)

add_custom_command(OUTPUT
    c_hshlexer.yy.cpp
    PRE_BUILD
    COMMAND
    flex -o c_hshlexer.yy.cpp  ../hshlex.l
    DEPENDS
    hshlex.l
)
add_executable(Lexer c_lexer.cpp main.cpp c_hshlexer.yy.cpp)

include_directories(${PROJECT_SOURCE_DIR})


