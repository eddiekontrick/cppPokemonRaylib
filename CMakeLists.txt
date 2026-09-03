cmake_minimum_required(VERSION 3.20)

project(cppRaylibPokemon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

find_package(tinyxml2 CONFIG QUIET)

if(NOT tinyxml2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG 11.0.0
    )
    FetchContent_MakeAvailable(tinyxml2)
endif()

add_executable(cppRaylibPokemon
    src/main.cpp
)

target_link_libraries(cppRaylibPokemon PRIVATE raylib tinyxml2)

add_custom_command(TARGET cppRaylibPokemon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:cppRaylibPokemon>/assets)