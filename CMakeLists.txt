cmake_minimum_required (VERSION 3.2)
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

message("Current output directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

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
set(CSC_SOURCES "src/csc.h" "src/csc.c" "src/cvector.h" "src/cvector.c" "src/cbitset.h" "src/cbitset.c" "src/cbst.h" "src/cbst.c")
add_library(csc STATIC ${CSC_SOURCES})

# Generate the unit tests
if (WIN32)
    message(FATAL_ERROR "Test builds not yet supported on Windows! You can still use the library sources though!")
elseif (APPLE)
    message(FATAL_ERROR "Test builds not yet supported on MacOS! You can still use the library sources though!")
elseif (UNIX AND NOT APPLE)
    add_custom_target(csc-build-tests 
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/make-tests.sh 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
else ()
    message(FATAL_ERROR "Unsupported operating system!")
endif()

# Build the tests for ctest
add_executable(csc-tests "test/tests.c" "test/CuTest.c" "test/CuTest.h" "test/cvector_tests.c" "test/cbitset_tests.c" "test/cbst_tests.c")
target_link_libraries(csc-tests csc)
add_dependencies(csc-tests csc-build-tests)

# Generate documentation if configured to.
if (CSC_GENERATE_DOCS)
    message("Generating doxygen documentation...")
    find_package(Doxygen REQUIRED)
    
    # Doxygen has been found. Set necessary doxygen config parameters.
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C "YES")
    set(DOXYGEN_PROJECT_NUMBER "1.0.0")
    set(DOXYGEN_PROJECT_BRIEF "C Standard Containers")
    set(DOXYGEN_GENERATE_LATEX "YES")
    set(DOXYGEN_GENERATE_HTML "NO")
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc")
    set(DOXYGEN_PREDEFINED "__CSC_DOXYGEN__")
    doxygen_add_docs(csc-docs "${CMAKE_CURRENT_SOURCE_DIR}/src")

    if (APPLE OR UNIX)
        add_custom_target(csc-build-docs
            ALL 
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate-docs.sh ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.csc-docs
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating doxygen documentation to ${DOXYGEN_OUTPUT_DIRECTORY}."
            VERBATIM)
    else ()
        message(FATAL_ERROR "Document generation not currently supported for this platform.")
    endif() # end OS check

endif() # end generate docs
