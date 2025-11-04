#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size) {
    matrix_t matrix(size, std::vector<int>(size, 0));
    if (size == 0) {
        return matrix;
    }

    int top = 0;
    int left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;

    int value = 1;
    while (top <= bottom && left <= right) {
        // left -> right
        for (int col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // top -> bottom
        for (int row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // right -> left
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // bottom -> top
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
