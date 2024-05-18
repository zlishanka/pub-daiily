cmake_minimum_required(VERSION 3.5) 

project(blur_image)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add blur_image executable
add_executable(blur_image main.cpp)

# Link OpenCV libraries
target_link_libraries(blur_image ${OpenCV_LIBS})
