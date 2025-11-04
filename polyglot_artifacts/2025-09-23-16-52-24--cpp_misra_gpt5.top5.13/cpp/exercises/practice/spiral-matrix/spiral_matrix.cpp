#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix
{
    const std::size_t n = size;
    if ((n == static_cast<std::size_t>(0U))) {
        return matrix{};
    }

    matrix result(
        n,
        std::vector<int>(n, 0)
    );

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t bottom = (n - static_cast<std::size_t>(1U));
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t right = (n - static_cast<std::size_t>(1U));

    int val = 1;

    while (((top <= bottom) && (left <= right))) {
        // Left to right across the top row
        for (std::size_t col = left; (col <= right); ++col) {
            result[top][col] = val;
            ++val;
        }

        if ((top == bottom)) {
            // Single remaining row handled; spiral complete
            break;
        }
        ++top;

        // Top to bottom down the right column
        for (std::size_t row = top; (row <= bottom); ++row) {
            result[row][right] = val;
            ++val;
        }

        if ((left == right)) {
            // Single remaining column handled; spiral complete
            break;
        }
        --right;

        // Right to left across the bottom row
        {
            std::size_t col = right;
            while (true) {
                result[bottom][col] = val;
                ++val;

                if ((col == left)) {
                    break;
                } else {
                    --col;
                }
            }
        }
        --bottom;

        // Bottom to top up the left column
        {
            std::size_t row = bottom;
            while (true) {
                result[row][left] = val;
                ++val;

                if ((row == top)) {
                    break;
                } else {
                    --row;
                }
            }
        }
        ++left;
    }

    return result;
}

}  // namespace spiral_matrix
