cmake_minimum_required(VERSION 2.8)
project( corretor )
set(OpenCV_DIR /opt/opencv/release)

find_package( OpenCV 4.0 REQUIRED )


include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( feactures feactures.cpp )
target_link_libraries( feactures ${OpenCV_LIBS} )
