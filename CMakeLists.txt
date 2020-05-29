cmake_minimum_required(VERSION 3.1) 
project(yolov3-trt)            

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE sources  modules/*.cpp modules/*.cu)
add_executable(yolov3-trt samples/sample_detector.cpp)

find_Package(gflags REQUIRED)

if(gflags_FOUND)
message("-- gflags found")
endif()

set(CMAKE_CXX_COMPILIER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

set(TensorRT_ROOT /usr/local/TensorRT)

include(cmake/cuda_stuff.cmake)
include(cmake/find_tensorrt.cmake)

find_package(OpenCV REQUIRED)

#generate detector lib
cuda_add_library(detector SHARED ${sources})
target_include_directories(detector PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/modules
  ${CMAKE_CURRENT_SOURCE_DIR}/extra
  ${OpenCV_INCLUDE_DIRS}
  ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
  ${TensorRT_INCLUDE_DIRS})

target_link_libraries(detector ${TensorRT_LIBRARY} gflags "stdc++fs")
				  
target_include_directories(yolov3-trt PRIVATE modules/ extra/)
target_link_libraries(yolov3-trt detector ${OpenCV_LIBS})


