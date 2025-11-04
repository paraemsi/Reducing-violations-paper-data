#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral(std::size_t size) {
    matrix_t matrix{};

    if (size == static_cast<std::size_t>(0U)) {
        return matrix;
    }

    matrix = matrix_t(size, std::vector<int>(size, 0));

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t bottom = static_cast<std::size_t>(size - static_cast<std::size_t>(1U));
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t right = static_cast<std::size_t>(size - static_cast<std::size_t>(1U));

    int value = 1;

    while ((left <= right) && (top <= bottom)) {
        for (std::size_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        for (std::size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            ++value;
        }
        if (right == static_cast<std::size_t>(0U)) {
            break;
        }
        --right;

        if (top <= bottom) {
            for (std::size_t col = right; ; --col) {
                matrix[bottom][col] = value;
                ++value;
                if (col == left) {
                    break;
                }
            }
            if (bottom == static_cast<std::size_t>(0U)) {
                break;
            }
            --bottom;
        }

        if (left <= right) {
            for (std::size_t row = bottom; ; --row) {
                matrix[row][left] = value;
                ++value;
                if (row == top) {
                    break;
                }
            }
            ++left;
        }
    }

    return matrix;
}

matrix_t spiral_matrix(std::size_t size) {
    return spiral(size);
}

}  // namespace spiral_matrix
