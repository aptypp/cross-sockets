cmake_minimum_required(VERSION 3.27)
project(cross_sockets C)

set(CMAKE_C_STANDARD 23)

set(CHOOSE_TARGET_PLATFORM_AUTO true)
set(TARGET_IS_WINDOWS true)

if (CHOOSE_TARGET_PLATFORM_AUTO)
    if (WIN32)
        set(TARGET_IS_WINDOWS true)
    else ()
        set(TARGET_IS_WINDOWS false)
    endif ()
endif ()


if (TARGET_IS_WINDOWS)
    message(STATUS "TARGET FOR WINDOWS")
else ()
    message(STATUS "TARGET FOR LINUX")
endif ()

if (TARGET_IS_WINDOWS)
    FILE(GLOB PLATFORM_DEPENDENT_SRC src/windows/*.c)
else ()
    FILE(GLOB PLATFORM_DEPENDENT_SRC src/linux/*.c)
endif ()

FILE(GLOB INDEPENDENT_SRC src/*.c)

add_library(cross_sockets SHARED ${INDEPENDENT_SRC}
        ${PLATFORM_DEPENDENT_SRC})

target_include_directories(cross_sockets PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(cross_sockets_test src/main.c)

target_link_libraries(cross_sockets_test PRIVATE cross_sockets)