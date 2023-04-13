cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Werror -Wpedantic -Wextra)
project(dz2 VERSION 0.1.0)

add_subdirectory(lib/utils)

add_executable(dz2 src/main.cpp)

target_link_libraries(dz2 utils)
