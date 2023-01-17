cmake_minimum_required(VERSION 3.15)

project("curl-playground")

add_executable(app main.cpp)

target_compile_options(app PRIVATE -Wall -Wextra -Werror -pedantic-errors)
