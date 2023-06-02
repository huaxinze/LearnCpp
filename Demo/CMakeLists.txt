cmake_minimum_required(VERSION 3.5)

project(ifly_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} " CACHE STRING "Set C++ Compile Flags" FORCE)

# create a library
add_library(ifly_library SHARED ${PROJECT_SOURCE_DIR}/IflyVersion0/ifly0.cpp)

# create a executable
add_executable(ifly_test main.cpp)
target_link_libraries(ifly_test ifly_library dl)
target_include_directories(ifly_test PUBLIC ${PROJECT_SOURCE_DIR}/include)


############################################################
# Install
############################################################
# bin
install(TARGETS ifly_test DESTINATION /usr/bin)
# lib
install(TARGETS ifly_library LIBRARY DESTINATION /usr/lib)