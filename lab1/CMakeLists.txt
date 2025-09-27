cmake_minimum_required(VERSION 3.10)
project(Lab1 LANGUAGES C)

# Настройка стандарта C (C99)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(myMath src/myMath.c)
add_executable(build main.c)

target_link_libraries(build PRIVATE myMath)

# Добавление тестов
# enable_testing()

# add_executable(tests tests/test.c)
# target_link_libraries(tests PRIVATE myMath)

# Добавление тестов в тестовый набор
# add_test(NAME MyProjectTests COMMAND tests)

# Базовые флаги компиляции для C
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(my_app PRIVATE -Wall -Wextra -pedantic)

endif()




