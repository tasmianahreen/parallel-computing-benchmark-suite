#pragma once
#include "matrix.hpp"

void matmul_openmp(const Matrix &A, const Matrix &B, Matrix &C, int n);
