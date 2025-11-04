#include "spiral_matrix.h"

namespace spiral_matrix {

namespace {
    std::vector<std::vector<unsigned int>> build_spiral(std::size_t n) {
        if (n == 0) {
            return {};
        }

        std::vector<std::vector<unsigned int>> matrix(n, std::vector<unsigned int>(n, 0));
        int top = 0, bottom = static_cast<int>(n) - 1, left = 0, right = static_cast<int>(n) - 1;
        unsigned int val = 1;

        while (left <= right && top <= bottom) {
            // Fill top row (left to right)
            for (int j = left; j <= right; ++j) {
                matrix[top][j] = val++;
            }
            // Fill right column (top to bottom)
            for (int i = top + 1; i <= bottom; ++i) {
                matrix[i][right] = val++;
            }
            // Fill bottom row and left column if there is an inner rectangle
            if (top < bottom && left < right) {
                // Bottom row (right to left)
                for (int j = right - 1; j >= left; --j) {
                    matrix[bottom][j] = val++;
                }
                // Left column (bottom to top)
                for (int i = bottom - 1; i > top; --i) {
                    matrix[i][left] = val++;
                }
            }

            ++top;
            --bottom;
            ++left;
            --right;
        }

        return matrix;
    }
}  // namespace



std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    return build_spiral(size);
}

}  // namespace spiral_matrix
