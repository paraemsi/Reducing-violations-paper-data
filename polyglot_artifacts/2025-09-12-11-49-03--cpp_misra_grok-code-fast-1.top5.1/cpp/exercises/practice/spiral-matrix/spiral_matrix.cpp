#include "spiral_matrix.h"

#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size) {
    if (size == static_cast<std::uint32_t>(0)) {
        return {};
    }
    std::vector<std::vector<std::uint32_t>> matrix(size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0)));
    std::uint32_t num = static_cast<std::uint32_t>(1);
    std::uint32_t top = static_cast<std::uint32_t>(0);
    std::uint32_t bottom = (size - static_cast<std::uint32_t>(1));
    std::uint32_t left = static_cast<std::uint32_t>(0);
    std::uint32_t right = (size - static_cast<std::uint32_t>(1));
    while ((top <= bottom) && (left <= right)) {
        {
            for (std::uint32_t j = left; j <= right; j++) {
                matrix[top][j] = num;
                num++;
            }
        }
        top++;
        {
            for (std::uint32_t i = top; i <= bottom; i++) {
                matrix[i][right] = num;
                num++;
            }
        }
        right--;
        if (top <= bottom) {
            {
                for (std::uint32_t j = right; ; j--) {
                    matrix[bottom][j] = num;
                    num++;
                    if (j == left) {
                        break;
                    }
                }
            }
            bottom--;
        }
        if (left <= right) {
            {
                for (std::uint32_t i = bottom; ; i--) {
                    matrix[i][left] = num;
                    num++;
                    if (i == top) {
                        break;
                    }
                }
            }
            left++;
        }
    }
    return matrix;
}

}  // namespace spiral_matrix
