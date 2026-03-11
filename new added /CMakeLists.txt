cmake_minimum_required(VERSION 3.10)

# 1. Project Name
project(JSON_Processor)

# 2. Set C++ Standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Add Files
# Make sure json.hpp is in the same directory!
add_executable(JSON_TEST main.cpp)

# 4. Include current directory (where json.hpp is)
target_include_directories(JSON_TEST PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Link filesystem (Required for some older compilers/OS)
target_link_libraries(JSON_TEST stdc++fs)