cmake_minimum_required(VERSION 2.8)
project( Contraste )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Contraste Contraste.cpp )
target_link_libraries( Contraste ${OpenCV_LIBS} )
