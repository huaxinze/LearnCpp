cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_cmake)

# Find thread lib
find_package(Threads)

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Link thread lib
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})