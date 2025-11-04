#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));
    if (size == 0) {
        return result;
    }

    int top = 0;
    int left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;

    int value = 1;

    while (left <= right && top <= bottom) {
        // Top row: left -> right
        for (int c = left; c <= right; ++c) {
            result[static_cast<std::size_t>(top)][static_cast<std::size_t>(c)] = value++;
        }
        ++top;

        // Right column: top -> bottom
        for (int r = top; r <= bottom; ++r) {
            result[static_cast<std::size_t>(r)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // Bottom row: right -> left
        if (top <= bottom) {
            for (int c = right; c >= left; --c) {
                result[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(c)] = value++;
            }
            --bottom;
        }

        // Left column: bottom -> top
        if (left <= right) {
            for (int r = bottom; r >= top; --r) {
                result[static_cast<std::size_t>(r)][static_cast<std::size_t>(left)] = value++;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
