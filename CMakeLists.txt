cmake_minimum_required(VERSION 3.10)
project(cimg_lab)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/modules)

# Find and link X11 libraries (required for CImg display)
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

# Add the main executable and link files
add_executable(cimg_lab src/main.cpp src/modules/gradient.cpp)
target_link_libraries(cimg_lab ${X11_LIBRARIES})
