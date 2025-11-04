#include "spiral_matrix.h"
#include <array>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>> {
    if (size == static_cast<std::uint32_t>(0)) {
        return {};
    }

    std::vector<std::vector<std::uint32_t>> matrix(
        static_cast<std::size_t>(size),
        std::vector<std::uint32_t>(static_cast<std::size_t>(size), 0U));

    static constexpr std::array<std::int32_t, 4U> d_row = {0, 1, 0, -1};
    static constexpr std::array<std::int32_t, 4U> d_col = {1, 0, -1, 0};

    std::int32_t row = 0;
    std::int32_t col = 0;
    std::uint32_t dir_index = 0U;

    for (std::uint32_t val = 1U; val <= (size * size); ++val) {
        matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] = val;

        std::int32_t next_row =
            static_cast<std::int32_t>(row) +
            d_row[static_cast<std::size_t>(dir_index)];
        std::int32_t next_col =
            static_cast<std::int32_t>(col) +
            d_col[static_cast<std::size_t>(dir_index)];

        bool need_turn = ((next_row < 0) ||
                          (next_row >= static_cast<std::int32_t>(size)) ||
                          (next_col < 0) ||
                          (next_col >= static_cast<std::int32_t>(size)) ||
                          (matrix[static_cast<std::size_t>(next_row)]
                                 [static_cast<std::size_t>(next_col)] != 0U));

        if (need_turn) {
            dir_index = (dir_index + 1U) % 4U;
            next_row = static_cast<std::int32_t>(row) +
                       d_row[static_cast<std::size_t>(dir_index)];
            next_col = static_cast<std::int32_t>(col) +
                       d_col[static_cast<std::size_t>(dir_index)];
        }

        row = next_row;
        col = next_col;
    }

    return matrix;
}

}  // namespace spiral_matrix
