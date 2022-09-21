cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(RayTracer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES_DIRECTORY  "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE SRC_FILES
    "${SOURCES_DIRECTORY}/*.cpp"
    "${SOURCES_DIRECTORY}/*.h"
)

add_executable(${PROJECT_NAME} "${SRC_FILES}")

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/3rd-party"
    "${CMAKE_SOURCE_DIR}/src/includes"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
