cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(RayTracer CXX)

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_executable(${PROJECT_NAME} "${SRC_FILES}")

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/3rd-party"
    "${CMAKE_SOURCE_DIR}/includes"
)