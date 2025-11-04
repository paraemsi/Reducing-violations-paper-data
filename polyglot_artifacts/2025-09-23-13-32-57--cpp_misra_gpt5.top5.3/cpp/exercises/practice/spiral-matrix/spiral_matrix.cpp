#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size) {
    if (size == static_cast<std::size_t>(0U)) {
        return matrix_t{};
    }

    matrix_t result(size, std::vector<int>(size, 0));

    int val = 1;

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t bottom = (size - static_cast<std::size_t>(1U));
    std::size_t right = bottom;

    while ((top <= bottom) && (left <= right)) {
        for (std::size_t col = left; col <= right; ++col) {
            result[top][col] = val;
            ++val;
        }
        ++top;

        for (std::size_t row = top; row <= bottom; ++row) {
            result[row][right] = val;
            ++val;
        }
        if (right > static_cast<std::size_t>(0U)) {
            --right;
        } else {
            right = static_cast<std::size_t>(0U);
        }

        if (top <= bottom) {
            for (std::size_t col = right + static_cast<std::size_t>(1U); col-- > left; ) {
                result[bottom][col] = val;
                ++val;
            }
            if (bottom > static_cast<std::size_t>(0U)) {
                --bottom;
            } else {
                bottom = static_cast<std::size_t>(0U);
            }
        }

        if (left <= right) {
            for (std::size_t row = bottom + static_cast<std::size_t>(1U); row-- > top; ) {
                result[row][left] = val;
                ++val;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
