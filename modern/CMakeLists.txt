cmake_minimum_required(VERSION 3.20)
project(Australia1859Sim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

# Raylib 5.5 - ultra lekka, szybka i niezawodna biblioteka graficzna
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(Australia1859Sim
    src/main.cpp
    src/Kroliki.cpp
    src/Lisy.cpp
    src/Simulation.cpp
)

target_include_directories(Australia1859Sim PRIVATE src)
target_link_libraries(Australia1859Sim PRIVATE raylib)

# Kopiuj sprite'y do folderu wynikowego po kompilacji
add_custom_command(TARGET Australia1859Sim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:Australia1859Sim>/assets"
)
