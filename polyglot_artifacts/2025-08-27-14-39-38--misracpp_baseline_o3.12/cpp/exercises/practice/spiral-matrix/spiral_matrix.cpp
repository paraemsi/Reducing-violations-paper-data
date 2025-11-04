#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    auto n = static_cast<int>(size);                     // cast once to a signed type
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size));
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    unsigned int value = 1;

    while (top <= bottom && left <= right) {
        // Traverse from Left to Right
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Traverse from Top to Bottom
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Traverse from Right to Left
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Traverse from Bottom to Top
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
