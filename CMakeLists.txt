cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(polinoms)

include(cmake/function.cmake)

add_subdirectory(polinoms)
add_subdirectory(main)

option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()
