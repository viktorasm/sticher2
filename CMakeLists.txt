cmake_minimum_required(VERSION 2.8)
project(sticher)

find_package( OpenCV 3.4 REQUIRED )

add_executable( sticher src/main.cpp src/candidate_points.cpp )
target_link_libraries( sticher ${OpenCV_LIBS} )