#include "spiral_matrix.h"

namespace spiral_matrix {

static std::vector<std::vector<int> > build_spiral(std::size_t size) {
    if (size == 0) {
        return std::vector<std::vector<int> >();
    }

    std::vector<std::vector<int> > result(size, std::vector<int>(size, 0));

    int top = 0;
    int left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;
    int value = 1;

    while (left <= right && top <= bottom) {
        for (int col = left; col <= right; ++col) {
            result[top][col] = value++;
        }
        ++top;

        for (int row = top; row <= bottom; ++row) {
            result[row][right] = value++;
        }
        --right;

        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                result[bottom][col] = value++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                result[row][left] = value++;
            }
            ++left;
        }
    }

    return result;
}

std::vector<std::vector<int> > spiral(std::size_t size) {
    return build_spiral(size);
}

std::vector<std::vector<int> > spiral_matrix(std::size_t size) {
    return spiral(size);
}

}  // namespace spiral_matrix
