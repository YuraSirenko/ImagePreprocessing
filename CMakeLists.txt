cmake_minimum_required(VERSION 3.31)
project(preprocess)

set(CMAKE_CXX_STANDARD 20)

set(OpenCV_DIR C:/opencv/opencv/build)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(preprocess main.cpp
        main.h
        bilateral_filtering.cpp
        edge_enhancement_laplacian.cpp
        edge_enhancement_laplacian.h
        bilateral_filtering.h
        io.cpp
        io.h
        clock.h)
target_link_libraries(preprocess ${OpenCV_LIBS})

target_compile_definitions(preprocess PRIVATE SMALL_COMPARE=1)
