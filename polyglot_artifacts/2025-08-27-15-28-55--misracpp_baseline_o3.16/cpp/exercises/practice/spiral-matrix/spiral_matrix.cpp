#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    if (size == 0) {
        return matrix;
    }

    int n = static_cast<int>(size);
    unsigned int num = 1;
    int row_start = 0, row_end = n - 1;
    int col_start = 0, col_end = n - 1;

    while (row_start <= row_end && col_start <= col_end) {
        // Move right across the top row.
        for (int col = col_start; col <= col_end; ++col) {
            matrix[row_start][col] = num++;
        }
        ++row_start;

        // Move down the rightmost column.
        for (int row = row_start; row <= row_end; ++row) {
            matrix[row][col_end] = num++;
        }
        --col_end;

        // Move left across the bottom row.
        if (row_start <= row_end) {
            for (int col = col_end; col >= col_start; --col) {
                matrix[row_end][col] = num++;
            }
            --row_end;
        }

        // Move up the leftmost column.
        if (col_start <= col_end) {
            for (int row = row_end; row >= row_start; --row) {
                matrix[row][col_start] = num++;
            }
            ++col_start;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
