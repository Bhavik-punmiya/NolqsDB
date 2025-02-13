cmake_minimum_required(VERSION 3.10)
project(groundupdb)

# Add this line to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(groundupdb STATIC
    Sources/groundupdb.cpp
    Sources/database.cpp
)

target_include_directories(groundupdb PUBLIC
    ${CMAKE_SOURCE_DIR}/Headers/include
    ${CMAKE_SOURCE_DIR}/Headers/include/extens
)

if(MSVC)
    target_compile_options(groundupdb PRIVATE /W4 /WX)
else()
    target_compile_options(groundupdb PRIVATE -Wall -Wextra -pedantic -Werror)
endif()