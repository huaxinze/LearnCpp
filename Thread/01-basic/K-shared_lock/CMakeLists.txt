cmake_minimum_required(VERSION 3.16)

project(shared_lock)

find_package(Threads REQUIRED)
if(Threads_FOUND)
    message("thread find")
else()
    message(FATAL_ERROR "can not find thread lib")
endif()

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})