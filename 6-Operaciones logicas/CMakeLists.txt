cmake_minimum_required(VERSION 2.8)
project( LogicOperations )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( LogicOperations LogicOperations.cpp )
target_link_libraries( LogicOperations ${OpenCV_LIBS} )
