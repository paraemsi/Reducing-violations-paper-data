#include "spiral_matrix.h"

#include <vector>

namespace spiral_matrix {

std::vector<std::vector<unsigned int> > spiral_matrix(int size) {
    std::vector<std::vector<unsigned int> > matrix(size, std::vector<unsigned int>(size, 0));
    unsigned int value = 1;
    int top = 0, bottom = size - 1;
    int left = 0, right = size - 1;

    while (top <= bottom && left <= right) {
        // Fill top row
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Fill right column
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Fill bottom row
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Fill left column
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
