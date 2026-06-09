#include "hip_matmul.hpp"
#include <hip/hip_runtime.h>
#include <stdexcept>
#include <sstream>

#define HIP_CHECK(call) do {                                      \
    hipError_t err = call;                                        \
    if (err != hipSuccess) {                                      \
        std::ostringstream oss;                                   \
        oss << "HIP error: " << hipGetErrorString(err)            \
            << " at " << __FILE__ << ":" << __LINE__;            \
        throw std::runtime_error(oss.str());                      \
    }                                                             \
} while (0)

__global__ void matmul_kernel(const float *A, const float *B, float *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        float sum = 0.0f;
        for (int k = 0; k < n; ++k) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

void matmul_hip(const Matrix &A, const Matrix &B, Matrix &C, int n) {
    const size_t bytes = static_cast<size_t>(n) * n * sizeof(float);

    float *d_A = nullptr;
    float *d_B = nullptr;
    float *d_C = nullptr;

    HIP_CHECK(hipMalloc(&d_A, bytes));
    HIP_CHECK(hipMalloc(&d_B, bytes));
    HIP_CHECK(hipMalloc(&d_C, bytes));

    HIP_CHECK(hipMemcpy(d_A, A.data(), bytes, hipMemcpyHostToDevice));
    HIP_CHECK(hipMemcpy(d_B, B.data(), bytes, hipMemcpyHostToDevice));

    dim3 block(16, 16);
    dim3 grid((n + block.x - 1) / block.x, (n + block.y - 1) / block.y);

    hipLaunchKernelGGL(matmul_kernel, grid, block, 0, 0, d_A, d_B, d_C, n);
    HIP_CHECK(hipGetLastError());
    HIP_CHECK(hipDeviceSynchronize());

    HIP_CHECK(hipMemcpy(C.data(), d_C, bytes, hipMemcpyDeviceToHost));

    HIP_CHECK(hipFree(d_A));
    HIP_CHECK(hipFree(d_B));
    HIP_CHECK(hipFree(d_C));
}
