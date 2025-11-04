#include "spiral_matrix.h"

#include <vector>

namespace spiral_matrix {

std::vector<std::vector<unsigned int> > spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int> > out(size, std::vector<unsigned int>(size, 0));
    if (size == 0) {
        return out;
    }

    int top = 0;
    int left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;

    unsigned int val = 1;

    while (left <= right && top <= bottom) {
        // Top row: left -> right
        for (int j = left; j <= right; ++j) {
            out[top][j] = val++;
        }
        ++top;

        // Right column: top -> bottom
        for (int i = top; i <= bottom; ++i) {
            out[i][right] = val++;
        }
        --right;

        // Bottom row: right -> left
        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                out[bottom][j] = val++;
            }
            --bottom;
        }

        // Left column: bottom -> top
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                out[i][left] = val++;
            }
            ++left;
        }
    }

    return out;
}

}  // namespace spiral_matrix
