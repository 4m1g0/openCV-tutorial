cmake_minimum_required(VERSION 2.8)
project( luts )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ApplyLut ApplyLut.cpp )
target_link_libraries( ApplyLut ${OpenCV_LIBS} )
