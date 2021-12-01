cmake_minimum_required(VERSION 3.10)

project(signature)

set(TARGET_PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

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
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pthread)

# Add tests
set(TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/signature.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/signature.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fileiterator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fileiterator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_signature.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_fileiterator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
        )

add_executable(test_${PROJECT_NAME} ${TEST_SOURCES})
target_include_directories(test_${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(test_${PROJECT_NAME} ${Boost_LIBRARIES} gtest pthread)

enable_testing()
add_test(test_${PROJECT_NAME} ${BUILD_DIR}/test_${PROJECT_NAME})