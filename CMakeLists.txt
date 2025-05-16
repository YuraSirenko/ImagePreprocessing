cmake_minimum_required(VERSION 3.31)
project(preprocess)

set(CMAKE_CXX_STANDARD 20)

set(OpenCV_DIR C:/opencv/opencv/build)

find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED CXX)


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(SYSTEM ${MPI_CXX_INCLUDE_PATH})

add_executable(preprocess main.cpp
        main.h
        bilateral_filtering.cpp
        edge_enhancement_laplacian.cpp
        edge_enhancement_laplacian.h
        bilateral_filtering.h
        io.cpp
        io.h
        clock.h
        computation.h
        computations.cpp
        helper.cpp
        helper.h)

target_link_libraries(preprocess PUBLIC
        ${OpenCV_LIBS}
        OpenMP::OpenMP_CXX
        MPI::MPI_CXX
)

add_custom_target(run_preprocess
        COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} 4
        $<TARGET_FILE:preprocess>
        DEPENDS preprocess
)
