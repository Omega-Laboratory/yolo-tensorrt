cmake_minimum_required(VERSION 3.10)
project(yolov3-trt LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CXX_SOURCES
  modules/class_detector.cpp
  modules/trt_utils.cpp
  modules/plugin_factory.cpp
  modules/yolo_config_parser.cpp
  modules/yolo.cpp
  modules/yolov2.cpp
  modules/yolov3.cpp
  modules/yoloplugin_lib.cpp
  modules/calibrator.cpp
  modules/ds_image.cpp
  modules/kernel.cu
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -Wno-write-strings \
  -Wno-unused-variable \
  -Wno-unused-function \
  -Wno-unused-but-set-variable \
  -Wno-deprecated-declarations")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

set(TensorRT_ROOT /usr/local/TensorRT)

include(cmake/cuda_stuff.cmake)
include(cmake/find_tensorrt.cmake)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(PythonLibs EXACT 3.6)
find_package(PythonInterp EXACT 3.6)
find_Package(gflags REQUIRED)

if(NOT gflags_FOUND)
 message(FATAL "gflags not found")
endif()

# generate detector lib
add_library(detector SHARED ${CXX_SOURCES})
target_link_libraries(detector PRIVATE ${CUDA_LIBRARIES} ${OpenCV_LIBS} ${TensorRT_LIBRARY} gflags "stdc++fs")
target_include_directories(detector PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/modules
  ${CMAKE_CURRENT_SOURCE_DIR}/extra
  ${OpenCV_INCLUDE_DIRS}
  ${CUDA_INCLUDE_DIRS}
  ${TensorRT_INCLUDE_DIRS})

#target_compile_definitions(detector PRIVATE -DAPI_EXPORTS)
#set_target_properties(detector PROPERTIES
#  POSITION_INDEPENDENT_CODE ON
#  CXX_VISIBILITY_PRESET "hidden"
#)

# generate detector python module
add_subdirectory(pybind11)
set(PYBIND11_CPP_STANDARD -std=c++14)

pybind11_add_module(pydetector MODULE THIN_LTO ${CMAKE_CURRENT_SOURCE_DIR}/wrapper/pydetector.cc)
target_link_libraries(pydetector PRIVATE ${CUDA_LIBRARIES} ${OpenCV_LIBS} ${TensorRT_LIBRARY} gflags "stdc++fs" detector)

# generate detector sample app
#add_executable(yolov3-trt samples/sample_detector.cpp)
#target_include_directories(yolov3-trt PUBLIC ${OpenCV_INCLUDE_DIRS} modules extra)
#target_link_libraries(yolov3-trt detector ${OpenCV_LIBS})

set(QT_IGNORE ${QT_QMAKE_EXECUTABLE})
