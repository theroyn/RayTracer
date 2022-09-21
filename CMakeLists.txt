cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(RayTracer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_executable(${PROJECT_NAME} "${SRC_FILES}")

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/3rd-party"
    "${CMAKE_SOURCE_DIR}/includes"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
