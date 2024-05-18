cmake_minimum_required(VERSION 3.2)

project(auto_croping)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG -DWITH_OPENCL=ON -DWITH_GSTREAMER=ON")
set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG -DWITH_OPENCL=ON -DWITH_IPP=ON")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package( OpenCV REQUIRED)

set(IMCROP_ROOT ../auto_cropping)

add_executable( imcrop main_imageautocrop.cpp ${IMCROP_ROOT}/src/ImageAutoCrop.cpp) 
#target_compile_definitions( imtile PUBLIC QNMSG)
include_directories( imcrop ${OpenCV_INCLUDE_DIRS} ${IMCROP_ROOT}/include  /usr/local/include ../Utils )
target_link_libraries( imcrop ${OpenCV_LIBS})
