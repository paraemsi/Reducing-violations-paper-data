#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int>> result;
    if (size == 0) {
        return result;
    }

    int n = static_cast<int>(size);
    result.assign(n, std::vector<unsigned int>(n, 0));

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    unsigned int value = 1;

    while (top <= bottom && left <= right) {
        for (int col = left; col <= right; ++col) {
            result[top][col] = value++;
        }
        ++top;

        for (int row = top; row <= bottom; ++row) {
            result[row][right] = value++;
        }
        --right;

        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                result[bottom][col] = value++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                result[row][left] = value++;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
