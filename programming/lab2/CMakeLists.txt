cmake_minimum_required(VERSION 3.0.0)

project(a.out)

file(GLOB SOURCES "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../)

target_link_libraries(${PROJECT_NAME} progbase m)

set(CMAKE_C_FLAGS "-g -std=c11 -Wall -Werror -Wno-unused")