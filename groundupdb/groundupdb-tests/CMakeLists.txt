# Define the test executable
add_executable(groundupdb-tests 
                    Sources/dbmanagement-tests.cpp
                    Sources/keyvalue-tests.cpp)


# Link with the static library
target_link_libraries(groundupdb-tests PRIVATE groundupdb)

target_include_directories(groundupdb-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/groundupdb-tests/Headers  
)

target_include_directories(groundupdb-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/groundupdb-tests/Sources  
)

# Ensure the executable builds after the library
add_dependencies(groundupdb-tests groundupdb)

# Use C++17 for this target
set_target_properties(groundupdb-tests PROPERTIES CXX_STANDARD 17)

# Set compile options based on the compiler
if(MSVC)
    target_compile_options(groundupdb-tests PRIVATE /W4)  # Use MSVC warning level 4
else()
    target_compile_options(groundupdb-tests PRIVATE -Wall -Wextra -pedantic)  # Use GCC/Clang flags
endif()

# Enable testing with CTest and register tests
enable_testing()
add_test(NAME GroundUpDBTests COMMAND groundupdb-tests)
