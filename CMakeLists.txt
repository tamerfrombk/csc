﻿cmake_minimum_required (VERSION 3.2)
project(csc)

set(CMAKE_C_STANDARD 99)

# Set additional compiler flags and link directories
if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Werror")
else()
    message(FATAL_ERROR "${CMAKE_C_COMPILER_ID} is not supported!")
endif()

# Set up the output directory for builds
set(CSC_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Set the generic runtime output directory for single generators like "make"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CSC_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CSC_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CSC_OUTPUT_DIR})

# Set the generic runtime output directory for multi generators like "msvc"
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CSC_OUTPUT_DIR}/${OUTPUTCONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CSC_OUTPUT_DIR}/${OUTPUTCONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CSC_OUTPUT_DIR}/${OUTPUTCONFIG})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

message("Current output directory ${CSC_OUTPUT_DIR}")

# Set the build type (this only affects single output generators)
if(CMAKE_GENERATOR MATCHES "Unix Makefiles")
    if(NOT CMAKE_BUILD_TYPE)
        message(WARNING "CMAKE_BUILD_TYPE was not specified. The build will default to a 'release' build type. Note that this only affects single configuration generators like Make and Ninja.")
        set(CMAKE_BUILD_TYPE "release")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
    else()
        message(STATUS "CMAKE_BUILD_TYPE set to ${CMAKE_BUILD_TYPE}")
        if(CMAKE_BUILD_TYPE MATCHES "debug")
            set(CMAKE_BUILD_TYPE "debug")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
        elseif(CMAKE_BUILD_TYPE MATCHES "release")
            set(CMAKE_BUILD_TYPE "release")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
        else()
            message(FATAL_ERROR "${CMAKE_BUILD_TYPE} is not supported for this generator! The only accepted values are 'debug' or 'release'!")
        endif()
    endif()
endif()

message("Compiling with: ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS}")

# Add additional include directories
include_directories(src)

# Build a library out of the sources
set(CSC_SOURCES "src/cvector.h" "src/cvector.c")
add_library(csc STATIC ${CSC_SOURCES})
set_target_properties(csc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CSC_OUTPUT_DIR}")

# Generate the unit tests
if (WIN32)
    message(FATAL_ERROR "Test builds not yet supported on Windows! You can still use the library sources though!")
elseif (APPLE)
    message(FATAL_ERROR "Test builds not yet supported on MacOS! You can still use the library sources though!")
elseif (UNIX AND NOT APPLE)
    add_custom_target(csc-build-tests COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/make-tests.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
else ()
    message(FATAL_ERROR "Unsupported operating system!")
endif()

# Build the tests for ctest
add_executable(csc-tests "test/tests.c" "test/CuTest.c" "test/CuTest.h")
target_link_libraries(csc-tests csc)
add_dependencies(csc-tests csc-build-tests)
set_target_properties(csc-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CSC_OUTPUT_DIR}")