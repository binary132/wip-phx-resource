project(foo C CXX)

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lz4/lib)

add_library(Res STATIC res.cxx res.hpp)
target_include_directories(Res PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${LZ4_INCLUDE_DIR})
target_link_libraries(Res LZ4)

add_executable(foo main.cxx)
target_link_libraries(foo Res)

set_property(TARGET foo PROPERTY CXX_STANDARD 11)
set_property(TARGET foo PROPERTY CXX_STANDARD_REQUIRED ON)
