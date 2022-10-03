cmake_minimum_required(VERSION 3.16)
project(Poor_dev_mgr)

set(CMAKE_CXX_STANDARD 20)

add_executable(Poor_dev_mgr main.cpp file_writer.h file_reader.h)
add_executable(test tests.cpp)
