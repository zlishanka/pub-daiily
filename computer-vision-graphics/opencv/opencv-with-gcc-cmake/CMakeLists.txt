cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( DisplayImage displayImage.cpp )
add_executable( WriteAlphaImage writeAlpha.cpp )
add_executable( VideoCapture videoCapture.cpp )
add_executable( CamShift camShift.cpp )

target_link_libraries( DisplayImage ${OpenCV_LIBS} ) 
target_link_libraries( WriteAlphaImage ${OpenCV_LIBS} ) 
target_link_libraries( VideoCapture ${OpenCV_LIBS} ) 
target_link_libraries( CamShift ${OpenCV_LIBS} ) 
