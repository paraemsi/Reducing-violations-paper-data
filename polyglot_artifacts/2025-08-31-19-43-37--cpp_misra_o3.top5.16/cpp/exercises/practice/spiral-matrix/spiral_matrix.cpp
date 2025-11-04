#include "spiral_matrix.h"
#include <cstdint>
#include <vector>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>> {
    /* Return an empty matrix for size 0 – simplifies later logic. */
    if (size == 0U) {
        return std::vector<std::vector<std::uint32_t>>{};
    }

    std::vector<std::vector<std::uint32_t>> matrix(
        size,
        std::vector<std::uint32_t>(size, 0U));

    std::uint32_t value   = 1U;
    const std::uint32_t layers = static_cast<std::uint32_t>(size / 2U);

    for (std::uint32_t layer = 0U; layer < layers; ++layer) {
        const std::uint32_t first = layer;
        const std::uint32_t last  = static_cast<std::uint32_t>(size - 1U) - layer;

        /* Top row (left-to-right). */
        for (std::uint32_t col = first; col <= last; ++col) {
            matrix[first][col] = value;
            ++value;
        }

        /* Right column (top-to-bottom). */
        for (std::uint32_t row = first + 1U; row <= last; ++row) {
            matrix[row][last] = value;
            ++value;
        }

        /* Bottom row (right-to-left) — only if there is more than one row in this layer. */
        if (first < last) {
            for (std::uint32_t col = last - 1U; col > first; --col) {
                matrix[last][col] = value;
                ++value;
            }

            /* Left column (bottom-to-top). */
            for (std::uint32_t row = last; row > first; --row) {
                matrix[row][first] = value;
                ++value;
            }
        }
    }

    /* If the matrix size is odd, place the final value in the centre. */
    if ((size % 2U) == 1U) {
        const std::uint32_t centre = size / 2U;
        matrix[centre][centre] = value;
    }

    return matrix;
}

}  // namespace spiral_matrix
