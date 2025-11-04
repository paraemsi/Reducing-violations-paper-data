#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int>> result(size, std::vector<unsigned int>(size, 0));
    if (size == 0) {
        return result;
    }

    int top = 0;
    int left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;
    unsigned int val = 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) {
            result[top][j] = val++;
        }
        ++top;

        for (int i = top; i <= bottom; ++i) {
            result[i][right] = val++;
        }
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                result[bottom][j] = val++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                result[i][left] = val++;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
