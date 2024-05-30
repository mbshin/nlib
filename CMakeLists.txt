cmake_minimum_required(VERSION 3.27)
project(nlib C)

set(CMAKE_C_STANDARD 11)

# Add the include and source directories
include_directories(include)
add_library(time_utils src/time_utils.c)

