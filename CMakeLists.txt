
cmake_minimum_required(VERSION 3.15)

project(My3DEngine C)

# -----------------------------
# Compiler settings
# -----------------------------
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(GENERATE_SCRIPT "${CMAKE_SOURCE_DIR}/src/bash_scripts/gen_ds.sh")

# -----------------------------
# Ensure required directories exist
# -----------------------------
file(MAKE_DIRECTORY
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_SOURCE_DIR}/src/data_structures/generated
)

# -----------------------------
# Raylib (FetchContent)
# -----------------------------
include(FetchContent)

FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz"
)

# Disable building examples and games
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FetchContent_MakeAvailable(raylib)

# -----------------------------
# Source files
# -----------------------------
file(GLOB_RECURSE PROJECT_SOURCES
    src/*.c
)

# Exclude templates from data_structures
list(FILTER PROJECT_SOURCES EXCLUDE REGEX "src/data_structures/templates/*")

# Ensure main.c exists
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/main.c")
    message(FATAL_ERROR "src/main.c not found!")
endif()

# -----------------------------
# Generate data structures
# -----------------------------
# Specify outputs (adjust if you know exact files generated)
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/src/data_structures/generated
    COMMAND bash ${GENERATE_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating data structures..."
    VERBATIM
)

# Custom target to run the generator
add_custom_target(generate_ds
    DEPENDS ${CMAKE_SOURCE_DIR}/src/data_structures/generated
)

# -----------------------------
# Executable
# -----------------------------
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Make sure generation runs before building executable
add_dependencies(${PROJECT_NAME} generate_ds)

# Run the program automatically after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Binary built, launching now..."
)

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/Models
        ${CMAKE_SOURCE_DIR}/src/data_structures/generated
)

# -----------------------------
# Link libraries
# -----------------------------
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)

# -----------------------------
# Linux-specific settings
# -----------------------------
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11)
endif()
