cmake_minimum_required(VERSION 3.24)
project(example LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-O3 -w -DWITH_OPENGL=ON -DHAVE_OPENGL=ON")
#set(CMAKE_BUILD_TYPE Release)


#find_package(PythonInterp REQUIRED)
#include_directories(${PYTHON_INCLUDE_DIRS})
#find_package(pybind11 REQUIRED)
#pybind11_add_module(example example.cpp)

find_package(OpenCV REQUIRED)

find_path(FOUNDATION_INCLUDE_DIR Foundation/Foundation.h)
include_directories(${FOUNDATION_INCLUDE_DIR})

set(APPLE_LIBS
        "-framework AVFoundation"
	"-framework CoreMedia"
	"-framework CoreVideo"
	"-framework Foundation"
	"-framework Metal"
	"-framework MetalKit"
	"-framework QuartzCore"
	"-framework IOKit"
	"-framework OpenGL"
	"-framework CoreGraphics"
	"-framework AppKit"
	"-framework OpenCL"

	#"-framework CoreFoundation"
	#"-framework CoreAudio"
	#"-framework CoreText"
	#"-framework Accelerate"
	#"-framework Security"
	#"-framework VideoToolbox"
	#"-framework AudioToolbox"
)


add_executable(imcam main_cam.cpp camera_avfoundation.mm GlRender.cpp )
#add_executable(imcam Cambak.mm )
include_directories(imcam ${OpenCV_INCLUDE_DIRS} /usr/local/include )
target_link_libraries(imcam PRIVATE ${OpenCV_LIBS} ${APPLE_LIBS} -L/usr/local/lib -lglfw -lglew)

#add_executable(imocv MultiCam.cpp)
#include_directories(imocv ${OpenCV_INCLUDE_DIRS} /usr/local/include )
#target_link_libraries(imocv PRIVATE ${OpenCV_LIBS} ${APPLE_LIBS} )

#add_executable(mrend metalrender.mm)
#include_directories(mrend ${OpenCV_INCLUDE_DIRS} /usr/local/include )
#target_link_libraries(mrend PRIVATE ${OpenCV_LIBS} ${APPLE_LIBS} )
