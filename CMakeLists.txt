cmake_minimum_required(VERSION 3.30)
project(vector C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES */*.c */*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})