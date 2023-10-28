cmake_minimum_required(VERSION 3.27)
project(cross_sockets C)

set(CMAKE_C_STANDARD 23)

add_library(cross_sockets SHARED src/cross_sockets.c
        src/ip_address.c)

target_include_directories(cross_sockets PUBLIC ${CMAKE_SOURCE_DIR}/include)
