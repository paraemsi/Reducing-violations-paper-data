#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    std::size_t top = 0;
    std::size_t bottom = size - 1;
    std::size_t left = 0;
    std::size_t right = size - 1;
    unsigned int current = 1;
    const unsigned int last = static_cast<unsigned int>(size) * static_cast<unsigned int>(size);

    while (current <= last) {
        // Fill top row: left -> right
        for (std::size_t col = left; col <= right && current <= last; ++col) {
            matrix[top][col] = current++;
        }
        ++top;

        // Fill right column: top -> bottom
        for (std::size_t row = top; row <= bottom && current <= last; ++row) {
            matrix[row][right] = current++;
        }
        --right;

        // Fill bottom row: right -> left
        for (std::size_t col = right + 1; col-- > left && current <= last; ) {
            matrix[bottom][col] = current++;
        }
        --bottom;

        // Fill left column: bottom -> top
        for (std::size_t row = bottom + 1; row-- > top && current <= last; ) {
            matrix[row][left] = current++;
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
