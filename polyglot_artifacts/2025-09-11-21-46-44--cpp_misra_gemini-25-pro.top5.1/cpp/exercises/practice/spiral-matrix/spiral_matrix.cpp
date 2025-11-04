#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    auto matrix = std::vector<std::vector<std::uint32_t>>(
        size, std::vector<std::uint32_t>(size));

    std::uint32_t num = 1;
    std::ptrdiff_t top = 0;
    std::ptrdiff_t bottom = static_cast<std::ptrdiff_t>(size) - 1;
    std::ptrdiff_t left = 0;
    std::ptrdiff_t right = static_cast<std::ptrdiff_t>(size) - 1;

    while ((top <= bottom) && (left <= right)) {
        // Fill top row
        for (std::ptrdiff_t i = left; i <= right; ++i) {
            matrix[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(i)] = num++;
        }
        top++;

        // Fill right column
        for (std::ptrdiff_t i = top; i <= bottom; ++i) {
            matrix[static_cast<std::size_t>(i)]
                  [static_cast<std::size_t>(right)] = num++;
        }
        right--;

        if (top <= bottom) {
            // Fill bottom row
            for (std::ptrdiff_t i = right; i >= left; --i) {
                matrix[static_cast<std::size_t>(bottom)]
                      [static_cast<std::size_t>(i)] = num++;
            }
            bottom--;
        }

        if (left <= right) {
            // Fill left column
            for (std::ptrdiff_t i = bottom; i >= top; --i) {
                matrix[static_cast<std::size_t>(i)]
                      [static_cast<std::size_t>(left)] = num++;
            }
            left++;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
