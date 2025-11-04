#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    unsigned int value = 1;
    int top = 0;
    int bottom = static_cast<int>(size) - 1;
    int left = 0;
    int right = static_cast<int>(size) - 1;

    while (top <= bottom && left <= right) {
        // Fill the top row (left to right)
        for (int col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // Fill the right column (top to bottom)
        for (int row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // Fill the bottom row (right to left)
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)]
                      [static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // Fill the left column (bottom to top)
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[static_cast<std::size_t>(row)]
                      [static_cast<std::size_t>(left)] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
