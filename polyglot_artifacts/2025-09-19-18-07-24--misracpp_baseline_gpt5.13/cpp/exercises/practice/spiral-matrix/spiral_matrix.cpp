#include "spiral_matrix.h"

namespace spiral_matrix {

static std::vector<std::vector<int>> spiral(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));

    int n = static_cast<int>(size);
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    int value = 1;

    while (top <= bottom && left <= right) {
        // Top row: left -> right
        for (int c = left; c <= right; ++c) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(c)] = value++;
        }
        ++top;

        // Right column: top -> bottom
        for (int r = top; r <= bottom; ++r) {
            matrix[static_cast<std::size_t>(r)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // Bottom row: right -> left
        if (top <= bottom) {
            for (int c = right; c >= left; --c) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(c)] = value++;
            }
            --bottom;
        }

        // Left column: bottom -> top
        if (left <= right) {
            for (int r = bottom; r >= top; --r) {
                matrix[static_cast<std::size_t>(r)][static_cast<std::size_t>(left)] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

std::vector<std::vector<int>> spiral_matrix(unsigned int size) {
    return spiral(static_cast<std::size_t>(size));
}

}  // namespace spiral_matrix
