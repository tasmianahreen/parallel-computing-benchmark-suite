# ROCm Parallel Computing Benchmark Suite

This project compares three matrix multiplication implementations:

1. CPU baseline in C++
2. OpenMP parallel CPU implementation
3. ROCm/HIP GPU implementation

## Requirements

- Linux
- CMake 3.21+
- C++17 compiler
- OpenMP
- ROCm installed with HIP support
- AMD GPU supported by ROCm

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build . -j
```

If CMake cannot detect your GPU architecture, specify it manually. Examples:

```bash
cmake .. -DCMAKE_HIP_ARCHITECTURES=gfx1030
cmake .. -DCMAKE_HIP_ARCHITECTURES=gfx1100
```

## Run

```bash
./benchmark 256
./benchmark 512
./benchmark 1024
```

The argument is the matrix size `N`, so `512` means multiplying two 512 x 512 matrices.

## Example Output

```text
Parallel Computing Benchmark Suite
Matrix multiplication size: 512 x 512

CPU baseline       time:  850.123 ms | max error: 0.000000e+00
OpenMP             time:  210.456 ms | max error: 0.000000e+00
ROCm/HIP           time:   35.891 ms | max error: 1.525879e-05

Speedup vs CPU:
OpenMP:   4.03x
ROCm/HIP: 23.69x
```

Your exact times will depend on your CPU, GPU, drivers, and matrix size.

