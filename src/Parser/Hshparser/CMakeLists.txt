cmake_minimum_required(VERSION 3.16)
project(PARSER)

set(CMAKE_CXX_STANDARD 17)

# 通过flex产生词法分析源代码
add_custom_command(OUTPUT
    hshlex.yy.cpp hshlex.yy.hpp
    PRE_BUILD
    COMMAND
    flex -o hshlex.yy.cpp --header=hshlex.yy.hpp ../hshlex.l
    DEPENDS
    hshlex.l
)

# 通过bison生成语法分析源代码
add_custom_command(OUTPUT
    hshparser.tab.cpp hshparser.tab.hpp
    PRE_BUILD
    COMMAND
    bison -d -o hshparser.tab.cpp --defines=hshparser.tab.hpp ../hshparser.y
    DEPENDS
    hshparser.y
)

add_executable(PARSER parser_main.cpp hshparser.tab.cpp hshlex.yy.cpp)

include_directories(${PROJECT_SOURCE_DIR}/myast)
include_directories(${PROJECT_SOURCE_DIR}/build)

target_link_libraries(PARSER -lfl)
