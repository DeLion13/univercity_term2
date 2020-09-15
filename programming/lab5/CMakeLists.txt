add_definitions(-std=c++17)
cmake_minimum_required(VERSION 3.0.0)

project(a.out)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../)