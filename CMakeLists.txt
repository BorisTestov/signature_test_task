cmake_minimum_required(VERSION 3.10)

project(signature)

if (CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "CMAKE_BUILD_TYPE not defined, 'Release' will be used")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# Set sources
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fileiterator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fileiterator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/signature.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/signature.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

        )

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS program_options filesystem)

# Add executables
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
