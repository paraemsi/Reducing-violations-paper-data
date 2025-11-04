#include "spiral_matrix.h"

namespace spiral_matrix {

matrix spiral_matrix(std::size_t size) {
    if ((size == std::size_t{0})) {
        return matrix{};
    }

    matrix mat(size, std::vector<std::uint32_t>(size, std::uint32_t{0}));

    std::size_t left = std::size_t{0};
    std::size_t right = size - std::size_t{1};
    std::size_t top = std::size_t{0};
    std::size_t bottom = size - std::size_t{1};

    std::uint32_t val = std::uint32_t{1};

    while ((left <= right) && (top <= bottom)) {
        for (std::size_t i = left; (i <= right); ++i) {
            mat[top][i] = val;
            ++val;
        }
        ++top;
        if (!((left <= right) && (top <= bottom))) {
            break;
        }

        for (std::size_t i = top; (i <= bottom); ++i) {
            mat[i][right] = val;
            ++val;
        }
        --right;
        if (!((left <= right) && (top <= bottom))) {
            break;
        }

        std::size_t i = right;
        while (true) {
            mat[bottom][i] = val;
            ++val;
            if ((i == left)) {
                break;
            }
            --i;
        }
        --bottom;
        if (!((left <= right) && (top <= bottom))) {
            break;
        }

        std::size_t j = bottom;
        while (true) {
            mat[j][left] = val;
            ++val;
            if ((j == top)) {
                break;
            }
            --j;
        }
        ++left;
    }

    return mat;
}

matrix spiral(std::size_t size) {
    return spiral_matrix(size);
}

}  // namespace spiral_matrix
