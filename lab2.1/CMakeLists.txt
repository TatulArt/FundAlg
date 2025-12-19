cmake_minimum_required(VERSION 3.10)
project(Lab2-1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(functions src/functions.c)
add_executable(build src/main.c)

target_link_libraries(build PRIVATE functions)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(build PRIVATE -Wall -Wextra -pedantic)


endif()