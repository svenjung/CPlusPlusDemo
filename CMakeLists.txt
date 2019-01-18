# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.4.1)
project(CPPDemo)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithm
)

aux_source_directory(. DIR_SRCS)

add_executable(CPPDemo ${DIR_SRCS})
