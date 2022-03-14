cmake_minimum_required(VERSION 2.8.12)
project(Bignum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(src)

add_subdirectory(src)
add_subdirectory(ut)