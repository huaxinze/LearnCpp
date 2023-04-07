cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_cmake)

# Add an executable
add_executable(hello_cmake main.cpp)

set_property(TARGET hello_cmake PROPERTY CXX_STANDARD 17)