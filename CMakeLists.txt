cmake_minimum_required(VERSION 3.21)

project(GameEngine LANGUAGES C CXX)

# ----------------------------------------
# Language standard
# ----------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------
# Collect source files (like your Makefile)
# ----------------------------------------
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/*.c
    core/*.cpp
    core/*.c
)

# ----------------------------------------
# Create executable
# ----------------------------------------
add_executable(game ${SRC_FILES})

# ----------------------------------------
# Include directories
# ----------------------------------------
target_include_directories(game PRIVATE
    src/engine/include
    third_party
    third_party/GLAD
    third_party/GLFW
    third_party/GLM
    third_party/KHR
    third_party/stb
)

# ----------------------------------------
# Compiler warnings
# ----------------------------------------
target_compile_options(game PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall>
)

# ----------------------------------------
# Libraries (Windows / Visual Studio)
# ----------------------------------------
if (WIN32)
    target_link_libraries(game PRIVATE
        opengl32
        gdi32
        glfw3
    )

    # If you still rely on MinGW-style libs in /lib
    target_link_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/lib)
endif()