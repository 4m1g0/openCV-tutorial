cmake_minimum_required(VERSION 2.8)
project( CalidadImagen )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( CalidadImagen CalidadImagen.cpp )
target_link_libraries( CalidadImagen ${OpenCV_LIBS} )
