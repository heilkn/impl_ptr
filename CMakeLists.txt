cmake_minimum_required(VERSION 3.13)

project(pimpl)

add_library(pimpl INTERFACE)
target_include_directories(pimpl INTERFACE "include")
target_compile_features(pimpl INTERFACE cxx_std_17)

option(BUILD_TESTS "Enable to build test." OFF)
if(${BUILD_TESTS})
	enable_testing()
	add_subdirectory("test")
endif()