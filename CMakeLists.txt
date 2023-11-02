cmake_minimum_required(VERSION 3.27)
project(cross_sockets C)

set(CMAKE_C_STANDARD 23)

#START platform settings

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

#END platform settings

set(IS_DYNAMIC_LIBRARY false)

#START cross_socket_library

if (TARGET_IS_WINDOWS)
    FILE(GLOB PLATFORM_DEPENDENT_SRC src/windows/*.c)
else ()
    FILE(GLOB PLATFORM_DEPENDENT_SRC src/linux/*.c)
endif ()

FILE(GLOB INDEPENDENT_SRC src/*.c)

if(${IS_DYNAMIC_LIBRARY})

add_library(cross_sockets SHARED ${INDEPENDENT_SRC}
        ${PLATFORM_DEPENDENT_SRC})
else ()
    add_library(cross_sockets STATIC ${INDEPENDENT_SRC}
            ${PLATFORM_DEPENDENT_SRC})
endif ()

if (TARGET_IS_WINDOWS)
    target_link_libraries(cross_sockets PRIVATE wsock32 ws2_32)
else ()
    #target_link_libraries(cross_sockets PRIVATE )
endif ()

target_include_directories(cross_sockets PUBLIC ${CMAKE_SOURCE_DIR}/include)

#END cross_sockets_library

#START client_executable
add_executable(client client/main.c)

target_link_libraries(client PRIVATE cross_sockets)

#END client_executable

#START server_executable
add_executable(server server/main.c)

target_link_libraries(server PRIVATE cross_sockets)

#END server_executable