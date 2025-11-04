#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(static_cast<std::size_t>(size),
                                                  std::vector<unsigned int>(static_cast<std::size_t>(size), 0u));

    int top = 0;
    int bottom = static_cast<int>(size) - 1;
    int left = 0;
    int right = static_cast<int>(size) - 1;
    unsigned int value = 1u;

    while (top <= bottom && left <= right) {
        // left -> right on top row
        for (int col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // top -> bottom on right column
        for (int row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // right -> left on bottom row
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // bottom -> top on left column
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
