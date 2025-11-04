#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix {
    if (size == static_cast<std::size_t>(0U)) {
        return matrix{};
    }

    matrix mat(size, std::vector<value_type>(size, value_type{0U}));

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t bottom = (size - static_cast<std::size_t>(1U));
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t right = (size - static_cast<std::size_t>(1U));

    value_type val = static_cast<value_type>(1U);

    while ((left <= right) && (top <= bottom)) {
        // left -> right
        for (std::size_t col = left; col <= right; ++col) {
            mat[top][col] = val;
            ++val;
        }
        ++top;

        // top -> bottom
        for (std::size_t row = top; row <= bottom; ++row) {
            mat[row][right] = val;
            ++val;
        }
        if (right > static_cast<std::size_t>(0U)) {
            --right;
        } else {
            right = static_cast<std::size_t>(0U);
        }

        // right -> left
        if (top <= bottom) {
            std::size_t col = right;
            while (true) {
                mat[bottom][col] = val;
                ++val;
                if (col == left) {
                    break;
                }
                --col;
            }
            if (bottom > static_cast<std::size_t>(0U)) {
                --bottom;
            } else {
                bottom = static_cast<std::size_t>(0U);
            }
        }

        // bottom -> top
        if ((left <= right) && (top <= bottom)) {
            std::size_t row = bottom;
            while (true) {
                mat[row][left] = val;
                ++val;
                if (row == top) {
                    break;
                }
                --row;
            }
            ++left;
        }
    }

    return mat;
}

}  // namespace spiral_matrix
