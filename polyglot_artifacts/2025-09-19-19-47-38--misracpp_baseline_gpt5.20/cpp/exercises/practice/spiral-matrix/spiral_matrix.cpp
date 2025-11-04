#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    int top = 0;
    int bottom = static_cast<int>(size) - 1;
    int left = 0;
    int right = static_cast<int>(size) - 1;
    unsigned int val = 1;

    while (top <= bottom && left <= right) {
        // Left to right across the top row
        for (int c = left; c <= right; ++c) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(c)] = val++;
        }
        ++top;

        // Top to bottom down the right column
        for (int r = top; r <= bottom; ++r) {
            matrix[static_cast<std::size_t>(r)][static_cast<std::size_t>(right)] = val++;
        }
        --right;

        // Right to left across the bottom row
        if (top <= bottom) {
            for (int c = right; c >= left; --c) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(c)] = val++;
            }
            --bottom;
        }

        // Bottom to top up the left column
        if (left <= right) {
            for (int r = bottom; r >= top; --r) {
                matrix[static_cast<std::size_t>(r)][static_cast<std::size_t>(left)] = val++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
