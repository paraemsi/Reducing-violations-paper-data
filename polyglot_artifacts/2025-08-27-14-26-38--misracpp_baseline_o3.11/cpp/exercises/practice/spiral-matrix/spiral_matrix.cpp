#include "spiral_matrix.h"
#include <vector>
#include <cstddef>

namespace spiral_matrix {

[[nodiscard]] std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    int n = static_cast<int>(size);
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;

    unsigned int value = 1;

    while (top <= bottom && left <= right) {
        // Traverse left to right along the top row.
        for (int col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // Traverse top to bottom along the right column.
        for (int row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // Traverse right to left along the bottom row.
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // Traverse bottom to top along the left column.
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
