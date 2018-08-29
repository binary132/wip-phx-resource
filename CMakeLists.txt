# TODO: get rid of "main" and just make it a functional test.
project(ResTest C CXX)

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add LZ4 and LZ4F definitions.
add_subdirectory(lz4/lib)

# Add Resource library.
add_library(Resource STATIC
  mapper.cxx
  mappings.cxx
  resource.cxx
  res/dat_txt.cxx
)

target_include_directories(Resource PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${LZ4F_INCLUDE_DIR}
)
target_link_libraries(Resource LZ4F)

set_property(TARGET Resource PROPERTY CXX_STANDARD 11)
set_property(TARGET Resource PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(ResTest main.cxx)
target_link_libraries(ResTest Resource)

set_property(TARGET ResTest PROPERTY CXX_STANDARD 11)
set_property(TARGET ResTest PROPERTY CXX_STANDARD_REQUIRED ON)
