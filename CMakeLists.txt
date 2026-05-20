cmake_minimum_required(VERSION 3.16)
project(asteroids VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAYLIB_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} main.cpp graphics_operations.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
