cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(foo CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(LZ4F_STATIC_LINKING_ONLY)

# This has an "add_library" statment in it, so we don't need to do more.
add_subdirectory(lz4/lib)
message("Found " ${LZ4_INCLUDE_DIR})

add_library(Res STATIC res.cxx)
target_include_directories(Res PUBLIC . ${LZ4_INCLUDE_DIR})
target_link_libraries(Res LZ4 STATIC)

add_executable(foo main.cxx)
target_link_libraries(foo Res)

