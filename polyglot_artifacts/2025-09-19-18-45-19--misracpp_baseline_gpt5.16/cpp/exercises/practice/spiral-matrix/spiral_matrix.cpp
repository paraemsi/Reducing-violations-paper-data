#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<int>> spiral(std::size_t size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    if (size == 0) {
        return matrix;
    }

    std::ptrdiff_t top = 0;
    std::ptrdiff_t bottom = static_cast<std::ptrdiff_t>(size) - 1;
    std::ptrdiff_t left = 0;
    std::ptrdiff_t right = static_cast<std::ptrdiff_t>(size) - 1;

    int current = 1;

    while (left <= right && top <= bottom) {
        // left -> right across the top row
        for (std::ptrdiff_t j = left; j <= right; ++j) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(j)] = current++;
        }
        ++top;
        if (top > bottom) break;

        // top -> bottom down the right column
        for (std::ptrdiff_t i = top; i <= bottom; ++i) {
            matrix[static_cast<std::size_t>(i)][static_cast<std::size_t>(right)] = current++;
        }
        --right;

        // right -> left across the bottom row
        if (top <= bottom) {
            for (std::ptrdiff_t j = right; j >= left; --j) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(j)] = current++;
            }
            --bottom;
        }

        // bottom -> top up the left column
        if (left <= right) {
            for (std::ptrdiff_t i = bottom; i >= top; --i) {
                matrix[static_cast<std::size_t>(i)][static_cast<std::size_t>(left)] = current++;
            }
            ++left;
        }
    }

    return matrix;
}


}  // namespace spiral_matrix
