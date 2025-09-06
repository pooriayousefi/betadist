cmake_minimum_required(VERSION 3.20)
project(betadist VERSION 1.0.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(betadist betadist/src.cpp)

# Set target properties
set_target_properties(betadist PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME betadist
)

# Compiler-specific options
if(MSVC)
    target_compile_options(betadist PRIVATE /W4 /permissive-)
else()
    target_compile_options(betadist PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Release optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        target_compile_options(betadist PRIVATE /O2)
    else()
        target_compile_options(betadist PRIVATE -O3 -DNDEBUG)
    endif()
endif()

# Platform-specific libraries
if(WIN32)
    # Windows-specific settings
elseif(APPLE)
    # macOS-specific settings
else()
    # Linux-specific settings
    target_link_libraries(betadist PRIVATE pthread)
endif()

# Install rules
install(TARGETS betadist
    RUNTIME DESTINATION bin
)

# Testing
enable_testing()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/")
    add_subdirectory(tests)
endif()
