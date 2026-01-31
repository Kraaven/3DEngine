cmake_minimum_required(VERSION 3.15)

project(My3DEngine C)

# -----------------------------
# Compiler settings
# -----------------------------
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# Create directories if missing
# -----------------------------
file(MAKE_DIRECTORY
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/resources
)

# -----------------------------
# Raylib (FetchContent)
# -----------------------------
include(FetchContent)

FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz"
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# -----------------------------
# Source files
# -----------------------------
file(GLOB_RECURSE PROJECT_SOURCES
    src/*.c
)

# Ensure main.c exists
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/main.c")
    message(FATAL_ERROR "src/main.c not found!")
endif()

# -----------------------------
# Executable
# -----------------------------
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

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

