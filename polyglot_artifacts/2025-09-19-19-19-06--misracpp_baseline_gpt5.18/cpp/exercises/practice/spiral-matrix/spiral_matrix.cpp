#include "spiral_matrix.h"

namespace spiral_matrix {

matrix spiral(std::size_t size) {
    matrix result;
    if (size == 0) {
        return result;
    }

    result.assign(size, std::vector<int>(size, 0));

    int top = 0;
    int left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;

    int value = 1;

    while (left <= right && top <= bottom) {
        // left -> right across the top row
        for (int col = left; col <= right; ++col) {
            result[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // top -> bottom down the right column
        for (int row = top; row <= bottom; ++row) {
            result[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // right -> left across the bottom row (if still within bounds)
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                result[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // bottom -> top up the left column (if still within bounds)
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                result[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value++;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
