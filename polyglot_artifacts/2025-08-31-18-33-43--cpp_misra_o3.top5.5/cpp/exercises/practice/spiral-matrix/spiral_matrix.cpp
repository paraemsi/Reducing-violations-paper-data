#include "spiral_matrix.h"

#include <cstdint>
#include <vector>
#include <array>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size)
    -> std::vector<std::vector<std::uint32_t>>
{
    /* Guard against a request for a zero-sized matrix. */
    if (size == static_cast<std::uint32_t>(0U)) {
        return {};
    }

    /* Pre-allocate a size × size matrix initialised with zeroes. */
    std::vector<std::vector<std::uint32_t>> matrix(
        size,
        std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    /* Direction vectors for right, down, left, and up movements. */
    const std::array<std::int32_t, 4> d_row {
        {static_cast<std::int32_t>(0),
         static_cast<std::int32_t>(1),
         static_cast<std::int32_t>(0),
         static_cast<std::int32_t>(-1)}};

    const std::array<std::int32_t, 4> d_col {
        {static_cast<std::int32_t>(1),
         static_cast<std::int32_t>(0),
         static_cast<std::int32_t>(-1),
         static_cast<std::int32_t>(0)}};

    std::int32_t row {static_cast<std::int32_t>(0)};
    std::int32_t col {static_cast<std::int32_t>(0)};
    std::uint32_t dir_index {static_cast<std::uint32_t>(0U)};

    const std::uint32_t total {static_cast<std::uint32_t>(size * size)};

    for (std::uint32_t value {static_cast<std::uint32_t>(1U)};
         value <= total;
         ++value) {
        /* Place the current value. */
        matrix[static_cast<std::uint32_t>(row)]
              [static_cast<std::uint32_t>(col)] = value;

        /* Compute tentative next coordinates. */
        std::int32_t next_row {row + d_row[static_cast<std::size_t>(dir_index)]};
        std::int32_t next_col {col + d_col[static_cast<std::size_t>(dir_index)]};

        const std::int32_t limit {static_cast<std::int32_t>(size)};
        const bool out_of_bounds { (next_row < static_cast<std::int32_t>(0)) ||
                                   (next_row >= limit) ||
                                   (next_col < static_cast<std::int32_t>(0)) ||
                                   (next_col >= limit) };

        const bool occupied { (!out_of_bounds) &&
                              (matrix[static_cast<std::uint32_t>(next_row)]
                                     [static_cast<std::uint32_t>(next_col)] !=
                               static_cast<std::uint32_t>(0U)) };

        if (out_of_bounds || occupied) {
            /* Rotate clockwise to the next direction. */
            dir_index = (dir_index + static_cast<std::uint32_t>(1U)) %
                        static_cast<std::uint32_t>(4U);

            next_row = row + d_row[static_cast<std::size_t>(dir_index)];
            next_col = col + d_col[static_cast<std::size_t>(dir_index)];
        }

        row = next_row;
        col = next_col;
    }

    return matrix;
}

}  // namespace spiral_matrix
