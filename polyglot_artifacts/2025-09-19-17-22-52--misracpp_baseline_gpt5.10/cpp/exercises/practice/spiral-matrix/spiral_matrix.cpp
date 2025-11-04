#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int>> result(size, std::vector<unsigned int>(size, 0u));
    if (size == 0) {
        return result;
    }

    int n = static_cast<int>(size);
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    unsigned int val = 1u;

    while (left <= right && top <= bottom) {
        // Top row: left -> right
        for (int col = left; col <= right; ++col) {
            result[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = val++;
        }
        ++top;

        // Right column: top -> bottom
        for (int row = top; row <= bottom; ++row) {
            result[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = val++;
        }
        --right;

        // Bottom row: right -> left
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                result[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = val++;
            }
            --bottom;
        }

        // Left column: bottom -> top
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                result[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = val++;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
