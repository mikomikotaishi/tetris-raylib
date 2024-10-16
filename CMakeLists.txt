cmake_minimum_required(VERSION 3.10)
project(Tetris VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -fsanitize=address -Wall -g -MMD -O2 -Werror=vla")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")

# Define source and include directories as variables
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include directories
include_directories(
    ${INCLUDE_DIR}
    ${SOURCE_DIR}/game
    ${SOURCE_DIR}/grid
    ${SOURCE_DIR}/piece
    ${SOURCE_DIR}/utility
)

# Source files
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/**/*.cpp"
)

list(APPEND SOURCES "${SOURCE_DIR}/main.cpp")

# Create the executable
add_executable(tetris ${SOURCES})

# Add specific include directories to the target
target_include_directories(tetris PRIVATE
    ${INCLUDE_DIR}               # Root include directory
)

# Link libraries
target_link_libraries(tetris
    raylib
    m
    pthread
    dl
    rt
    X11
)

# Add compiler flags
target_compile_options(tetris PRIVATE
    -fsanitize=address
)

# Set output directories for build artifacts
set_target_properties(tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Define the asset folder and copy it to the bin directory
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)  # Path to the assets folder (not inside src)
set(BUILD_ASSETS_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin/assets)  # Destination path in bin

# Add custom command to copy assets folder and subdirectories after building
add_custom_command(
    TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}/font ${BUILD_ASSETS_DIR}/font
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}/images ${BUILD_ASSETS_DIR}/images
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}/sounds ${BUILD_ASSETS_DIR}/sounds
    COMMENT "Copying font, images, and sounds to build directory"
)

# Optionally add a clean target for CMake
set_property(DIRECTORY APPEND PROPERTY CMAKE_MAKEFILE_LIST)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/*
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/Makefile
    COMMENT "Cleaning build files"
)

# Set the working directory for the executable
set_target_properties(tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)