cmake_minimum_required(VERSION 3.10)

# Top-level project name
project(groundupdb_project)

# Ensure all subprojects use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(groundupdb)
add_subdirectory(groundupdb-tests)
add_subdirectory(groundupdb-cli)