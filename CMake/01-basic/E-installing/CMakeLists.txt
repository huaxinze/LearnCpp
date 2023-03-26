cmake_minimum_required(VERSION 3.5)

project(cmake_examples_inst)

############################################################
# Create a library
############################################################
add_library(cmake_examples_inst SHARED src/Hello.cpp)
target_include_directories(cmake_examples_inst PUBLIC ${PROJECT_SOURCE_DIR}/include/installing)

############################################################
# Create an executable
############################################################
add_executable(cmake_examples_inst_bin src/main.cpp)
target_link_libraries(cmake_examples_inst_bin PRIVATE cmake_examples_inst)

############################################################
# Install
############################################################
# bin
install(TARGETS cmake_examples_inst_bin DESTINATION bin)
# lib
install(TARGETS cmake_examples_inst LIBRARY DESTINATION lib)
# header
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/installing DESTINATION include)
# config
install(FILES cmake-examples.conf DESTINATION etc)