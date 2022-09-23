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
    "${SOURCES_DIRECTORY}/*.hpp"
)

add_executable(${PROJECT_NAME} "${SRC_FILES}")

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/3rd-party"
    "${CMAKE_SOURCE_DIR}/src/includes"
)

set(EXTERNAL_LIBS
    Threads::Threads
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND EXTERNAL_LIBS
        tbb
    )
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
    "${EXTERNAL_LIBS}"
)
