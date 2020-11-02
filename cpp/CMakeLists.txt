cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(sudachi-sample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_library(sudachi-shared NAMES libsudachi.so PATHS /usr/local/lib)
set(sudachi-shared $ENV{LD_LIBRARY_PATH}/libsudachi.so)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sudachi-bin ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_link_libraries(sudachi-bin
    ${sudachi-shared})
set_target_properties(sudachi-bin PROPERTIES OUTPUT_NAME sample) 
