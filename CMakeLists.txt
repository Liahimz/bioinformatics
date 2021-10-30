cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/20.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(main ${SOURCE_FILES})


