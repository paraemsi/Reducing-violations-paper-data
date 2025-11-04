#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<int> > spiral_matrix(std::size_t size) {
    std::vector<std::vector<int> > m(size, std::vector<int>(size, 0));

    int n = static_cast<int>(size);
    int top = 0, left = 0;
    int bottom = n - 1, right = n - 1;

    int val = 1;

    while (top <= bottom && left <= right) {
        // top row: left -> right
        for (int c = left; c <= right; ++c) {
            m[top][c] = val++;
        }
        ++top;

        // right column: top -> bottom
        for (int r = top; r <= bottom; ++r) {
            m[r][right] = val++;
        }
        --right;

        // bottom row: right -> left
        if (top <= bottom) {
            for (int c = right; c >= left; --c) {
                m[bottom][c] = val++;
            }
            --bottom;
        }

        // left column: bottom -> top
        if (left <= right) {
            for (int r = bottom; r >= top; --r) {
                m[r][left] = val++;
            }
            ++left;
        }
    }

    return m;
}

}  // namespace spiral_matrix
