#pragma once
#include "matrix.hpp"

void matmul_hip(const Matrix &A, const Matrix &B, Matrix &C, int n);
