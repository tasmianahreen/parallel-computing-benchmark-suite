#include "matrix.hpp"
#include "timer.hpp"
#include "cpu_matmul.hpp"
#include "openmp_matmul.hpp"
#include "hip_matmul.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char **argv) {
    int n = 512;

    if (argc >= 2) {
        n = std::atoi(argv[1]);
        if (n <= 0) {
            std::cerr << "Matrix size must be positive.\n";
            return 1;
        }
    }

    std::cout << "Parallel Computing Benchmark Suite\n";
    std::cout << "Matrix multiplication size: " << n << " x " << n << "\n\n";

    Matrix A = random_matrix(n, 42);
    Matrix B = random_matrix(n, 123);

    Matrix C_cpu = create_matrix(n);
    Matrix C_openmp = create_matrix(n);
    Matrix C_hip = create_matrix(n);

    Timer timer;

    timer.reset();
    matmul_cpu(A, B, C_cpu, n);
    double cpu_ms = timer.elapsed_ms();
    print_summary("CPU baseline", cpu_ms);

    timer.reset();
    matmul_openmp(A, B, C_openmp, n);
    double openmp_ms = timer.elapsed_ms();
    print_summary("OpenMP", openmp_ms, max_abs_error(C_cpu, C_openmp));

    timer.reset();
    matmul_hip(A, B, C_hip, n);
    double hip_ms = timer.elapsed_ms();
    print_summary("ROCm/HIP", hip_ms, max_abs_error(C_cpu, C_hip));

    std::cout << "\nSpeedup vs CPU:\n";
    std::cout << "OpenMP:   " << cpu_ms / openmp_ms << "x\n";
    std::cout << "ROCm/HIP: " << cpu_ms / hip_ms << "x\n";

    return 0;
}
