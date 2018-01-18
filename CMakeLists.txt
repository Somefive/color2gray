cmake_minimum_required(VERSION 3.5)
project(Color2Gray)

set(CMAKE_CXX_STANDARD 11)
find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp utils.cpp utils.h Color2Gray.cpp Color2Gray.h)
add_executable(Color2Gray ${SOURCE_FILES})
target_link_libraries( Color2Gray ${OpenCV_LIBS} )