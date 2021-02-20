cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(converterRA)

include(cmake/function.cmake)

add_subdirectory(converterRA)
add_subdirectory(main)

option(BTEST "build test?" ON)

if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()
