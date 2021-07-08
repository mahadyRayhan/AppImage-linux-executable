cmake_minimum_required(VERSION 2.8.0)

project(hello-world-appimage)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src)
add_subdirectory(res)