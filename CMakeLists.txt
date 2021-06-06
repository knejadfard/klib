cmake_minimum_required(VERSION 3.18)

project(klib)

option(BUILD_TESTS "Build tests" ON)

add_library(klib INTERFACE)
target_include_directories(klib INTERFACE include/)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(BUILD_TESTS)
