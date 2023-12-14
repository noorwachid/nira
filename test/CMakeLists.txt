cmake_minimum_required(VERSION 3.11)

project("nira")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(".." "nira")

add_executable("nira-test" "source/main.cpp")
target_link_libraries("nira-test" "nira")


