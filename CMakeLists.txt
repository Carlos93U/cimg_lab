cmake_minimum_required(VERSION 3.10)
project(cimg_lab)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find and link X11 libraries
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})


# Add the main source file
add_executable(cimg_lab main.cpp)

# Link the X11 libraries to the executable
target_link_libraries(cimg_lab ${X11_LIBRARIES})