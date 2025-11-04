#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix
{
    if ((size == static_cast<std::size_t>(0U))) {
        return matrix{};
    }

    matrix result(size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t bottom = (size - static_cast<std::size_t>(1U));
    std::size_t right = (size - static_cast<std::size_t>(1U));

    std::uint32_t value = static_cast<std::uint32_t>(1U);

    while (((left <= right) && (top <= bottom))) {
        for (std::size_t col = left; col <= right; ++col) {
            result[top][col] = value;
            ++value;
        }
        ++top;
        if ((top > bottom)) {
            break;
        }

        for (std::size_t row = top; row <= bottom; ++row) {
            result[row][right] = value;
            ++value;
        }
        if ((left >= right)) {
            break;
        }
        --right;

        for (std::size_t col = right;; --col) {
            result[bottom][col] = value;
            ++value;
            if ((col == left)) {
                break;
            }
        }
        if ((top >= bottom)) {
            break;
        }
        --bottom;

        for (std::size_t row = bottom;; --row) {
            result[row][left] = value;
            ++value;
            if ((row == top)) {
                break;
            }
        }
        ++left;
    }

    return result;
}

}  // namespace spiral_matrix
