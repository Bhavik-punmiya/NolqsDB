# Define the CLI executable
add_executable(groundupdb-cli Sources/main.cpp)

# Link with the static library
target_link_libraries(groundupdb-cli PRIVATE groundupdb)

# Include directories for headers
target_include_directories(groundupdb-cli PRIVATE 
    ${CMAKE_SOURCE_DIR}/groundupdb/include
    ${CMAKE_SOURCE_DIR}/groundupdb-cli/Headers
    ${CMAKE_SOURCE_DIR}/external/cxxopts/include  # If using external dependencies
)

# Ensure CLI builds after the library
add_dependencies(groundupdb-cli groundupdb)

# Use C++17 for this target
set_target_properties(groundupdb-cli PROPERTIES CXX_STANDARD 17)

# Set compiler options
if(MSVC)
    target_compile_options(groundupdb-cli PRIVATE /W4)  
else()
    target_compile_options(groundupdb-cli PRIVATE -Wall -Wextra -pedantic)  
endif()
