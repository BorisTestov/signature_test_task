cmake_minimum_required(VERSION 3.10)

project(signature)

if (CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "CMAKE_BUILD_TYPE not defined, 'Release' will be used")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Set sources
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        )

# Add executables
add_executable(${PROJECT_NAME} ${SOURCES})