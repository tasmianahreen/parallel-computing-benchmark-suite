#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <iomanip>

using Matrix = std::vector<float>;

inline Matrix create_matrix(int n) {
    return Matrix(n * n, 0.0f);
}

inline Matrix random_matrix(int n, unsigned seed) {
    Matrix m(n * n);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (float &x : m) {
        x = dist(gen);
    }
    return m;
}

inline float max_abs_error(const Matrix &a, const Matrix &b) {
    float max_err = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        max_err = std::max(max_err, std::fabs(a[i] - b[i]));
    }
    return max_err;
}

inline void print_summary(const std::string &name, double ms, float error = 0.0f) {
    std::cout << std::left << std::setw(18) << name
              << " time: " << std::right << std::setw(10) << std::fixed << std::setprecision(3)
              << ms << " ms"
              << " | max error: " << std::scientific << error << std::fixed
              << "\n";
}
