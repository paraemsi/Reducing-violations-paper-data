#include "spiral_matrix.h"
#include <array>

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    const std::array<int, 4> dr{0, 1, 0, -1};  // row deltas: right, down, left, up
    const std::array<int, 4> dc{1, 0, -1, 0};  // col deltas: right, down, left, up

    int row = 0;
    int col = 0;
    std::size_t dir = 0;  // current direction index

    const unsigned int total = static_cast<unsigned int>(size * size);
    for (unsigned int value = 1; value <= total; ++value) {
        matrix[row][col] = value;

        int next_row = row + dr[dir];
        int next_col = col + dc[dir];

        if (next_row < 0 || next_row >= static_cast<int>(size) ||
            next_col < 0 || next_col >= static_cast<int>(size) ||
            matrix[next_row][next_col] != 0) {
            dir = (dir + 1) % 4;
            next_row = row + dr[dir];
            next_col = col + dc[dir];
        }

        row = next_row;
        col = next_col;
    }

    return matrix;
}

}  // namespace spiral_matrix
