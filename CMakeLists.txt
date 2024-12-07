cmake_minimum_required(VERSION 3.29)
project(progtest)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wextra -Wshadow -Wno-long-long -Wmaybe-uninitialized -Wsuggest-attribute=const -g -O2)

add_executable(_01 01/main.cpp)
add_executable(_02 02/main.cpp)
add_executable(_03 03/main.cpp)
add_executable(_04 04/main.cpp)
add_executable(_05 05/main.cpp)
add_executable(_06 06/main.cpp)
add_executable(_07 07/main.cpp)

