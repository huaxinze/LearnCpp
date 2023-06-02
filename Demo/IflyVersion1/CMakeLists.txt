cmake_minimum_required(VERSION 3.5)

project(ifly_library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} " CACHE STRING "Set C++ Compile Flags" FORCE)

# create ifly_library
add_library(ifly_library SHARED ifly1.cpp)
target_include_directories(ifly_library PUBLIC ${PROJECT_SOURCE_DIR})


############################################################
# Install
############################################################
install(TARGETS ifly_library LIBRARY DESTINATION /speech/ifly1)