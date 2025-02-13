# Define the test executable
add_executable(groundupdb-tests 
    Sources/dbmanagement-tests.cpp
    Sources/keyvalue-tests.cpp
)

# Link with the static library
target_link_libraries(groundupdb-tests PRIVATE groundupdb)

# Include test headers
target_include_directories(groundupdb-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/groundupdb/include
    ${CMAKE_SOURCE_DIR}/groundupdb-tests/Sources
)

# Ensure tests build after the library
add_dependencies(groundupdb-tests groundupdb)

# Use C++17 for this target
set_target_properties(groundupdb-tests PROPERTIES CXX_STANDARD 17)

# Set compiler options
if(MSVC)
    target_compile_options(groundupdb-tests PRIVATE /W4)  
else()
    target_compile_options(groundupdb-tests PRIVATE -Wall -Wextra -pedantic)  
endif()

# Enable testing with CTest
enable_testing()
add_test(NAME GroundUpDBTests COMMAND groundupdb-tests)
