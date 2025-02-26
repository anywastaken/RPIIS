cmake_minimum_required(VERSION 3.30)

project(pivo2)

set(SOURCE_EXE src/test.cpp)

set(SOURCE_LIB src/set.cpp)

add_library(set STATIC ${SOURCE_LIB})

add_executable(test ${SOURCE_EXE})

target_link_libraries(test gtest gmock pthread set)