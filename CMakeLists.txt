cmake_minimum_required(VERSION 3.29)
project(progtest)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wextra -Wshadow -Wno-long-long -Wmaybe-uninitialized -Wsuggest-attribute=const -g)

add_executable(_01 01/main.cpp)

