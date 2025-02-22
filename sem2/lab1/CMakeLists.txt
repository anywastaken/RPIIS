cmake_minimum_required(VERSION 3.26)
project(testtest)

set(CMAKE_CXX_STANDARD 20)

add_executable(testtest main.cpp stack.h
        stack.cpp)

add_subdirectory(Google_tests)