cmake_minimum_required(VERSION 2.8)
project( BayesClassifier )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( BayesClassifier BayesClassifier.cpp )
target_link_libraries( BayesClassifier ${OpenCV_LIBS} )
