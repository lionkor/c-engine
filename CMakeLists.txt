cmake_minimum_required(VERSION 3.15)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -pedantic-errors -Wfatal-errors -fanalyzer")

file(GLOB engine_sources
    "core/**.c" "utils/**.c"
)

include_directories(".")

message("sources: ${engine_sources}")

project(Engine)

add_library(Engine ${engine_sources})

target_link_libraries(Engine SDL2)

project(antsim-c)

add_executable(antsim-c main.c)

target_link_libraries(antsim-c Engine)
