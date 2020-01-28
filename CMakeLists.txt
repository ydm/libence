cmake_minimum_required (VERSION 3.0)
project (Libence VERSION 0.0.1 LANGUAGES CXX)

# Common include directories
include_directories (include)

# Targets

# loader_path + executable_path
add_executable (main src/main.cpp)

add_library (ence SHARED src/ence.cpp)
