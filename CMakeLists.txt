cmake_minimum_required(VERSION 3.21)
project(rocm_parallel_benchmark_suite LANGUAGES CXX HIP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_HIP_STANDARD 17)
set(CMAKE_HIP_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(benchmark
    src/main.cpp
    src/cpu_matmul.cpp
    src/openmp_matmul.cpp
    src/hip_matmul.hip
)

target_include_directories(benchmark PRIVATE src)
target_link_libraries(benchmark PRIVATE OpenMP::OpenMP_CXX)

# Helpful for AMD GPUs. You can override this when building:
# cmake -S . -B build -DCMAKE_HIP_ARCHITECTURES=gfx1100
if(NOT DEFINED CMAKE_HIP_ARCHITECTURES)
    set(CMAKE_HIP_ARCHITECTURES gfx900 gfx906 gfx908 gfx90a gfx1030 gfx1100 gfx1101 gfx1102)
endif()
