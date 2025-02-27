cmake_minimum_required(VERSION 3.22)
project("Queue")

find_package(GTest REQUIRED)

add_executable(a.out tests.cpp Node.cpp queue.cpp)

target_link_libraries(a.out ${GTEST_LIBRARIES})

enable_testing()

add_test(add a.out)
