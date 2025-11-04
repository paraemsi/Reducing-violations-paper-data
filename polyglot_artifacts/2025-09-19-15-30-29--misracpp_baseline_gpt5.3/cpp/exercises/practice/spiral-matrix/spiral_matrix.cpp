#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t generate(std::size_t size) {
    if (size == 0) {
        return {};
    }

    matrix_t m(size, std::vector<int>(size));

    int n = static_cast<int>(size);
    int top = 0, left = 0, bottom = n - 1, right = n - 1;
    int value = 1;

    while (top <= bottom && left <= right) {
        // Top row: left -> right
        for (int c = left; c <= right; ++c) {
            m[static_cast<std::size_t>(top)][static_cast<std::size_t>(c)] = value++;
        }
        // Right column: top+1 -> bottom
        for (int r = top + 1; r <= bottom; ++r) {
            m[static_cast<std::size_t>(r)][static_cast<std::size_t>(right)] = value++;
        }
        // Bottom row: right-1 -> left
        if (top < bottom) {
            for (int c = right - 1; c >= left; --c) {
                m[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(c)] = value++;
            }
        }
        // Left column: bottom-1 -> top+1
        if (left < right) {
            for (int r = bottom - 1; r > top; --r) {
                m[static_cast<std::size_t>(r)][static_cast<std::size_t>(left)] = value++;
            }
        }

        ++top;
        ++left;
        --bottom;
        --right;
    }

    return m;
}

matrix_t spiral_matrix(std::size_t size) {
    return generate(size);
}

}  // namespace spiral_matrix
