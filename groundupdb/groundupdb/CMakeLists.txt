# Define the static library
add_library(groundupdb STATIC 
    Sources/groundupdb.cpp
    Sources/database.cpp  
)


# Include the headers directory
target_include_directories(groundupdb PUBLIC 
    Headers
    Headers/include
    Headers/include/extensions
    )

# Use C++17 for this library
set_target_properties(groundupdb PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# Set compile options based on the compiler
if(MSVC)
    target_compile_options(groundupdb PRIVATE /W4)  # Use MSVC warning level 4
else()
    target_compile_options(groundupdb PRIVATE -Wall -Wextra -pedantic)  # Use GCC/Clang flags
endif()