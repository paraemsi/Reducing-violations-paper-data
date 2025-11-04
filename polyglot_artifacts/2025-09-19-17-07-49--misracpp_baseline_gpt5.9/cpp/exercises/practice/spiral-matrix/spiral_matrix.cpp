#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return std::vector<std::vector<unsigned int> >();
    }

    int n = static_cast<int>(size);
    std::vector<std::vector<unsigned int> > matrix(static_cast<std::size_t>(n),
                                         std::vector<unsigned int>(static_cast<std::size_t>(n)));

    int top = 0, left = 0;
    int bottom = n - 1, right = n - 1;
    unsigned int value = 1U;

    while (top <= bottom && left <= right) {
        // Top row: left -> right
        for (int col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // Right column: top -> bottom
        for (int row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // Bottom row: right -> left
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // Left column: bottom -> top
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
