cmake_minimum_required(VERSION 3.10)
project(JSON_TEST)

# Use C++20 for that Ryzen 5 performance
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. We don't need find_package anymore because the file is in your folder!
# We just tell CMake to look in the current directory for headers (.)
include_directories(.)

# 2. Define your executable
add_executable(JSON_TEST main.cpp)

# 3. No need to link a library (target_link_libraries)
# because nlohmann_json is "Header-Only".
# The compiler finds everything it needs in your main.cpp includes.