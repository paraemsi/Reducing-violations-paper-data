#include "spiral_matrix.h"

namespace spiral_matrix {

namespace {
matrix generate(std::size_t size) {
    matrix ret;

    if (size == 0U) {
        return ret;
    }

    ret = matrix(size, std::vector<value_type>(size, static_cast<value_type>(0U)));

    std::size_t left = 0U;
    std::size_t right = size - 1U;
    std::size_t top = 0U;
    std::size_t bottom = size - 1U;

    value_type val = static_cast<value_type>(1U);

    while ((left <= right) && (top <= bottom)) {
        // top row: left -> right at current top
        std::size_t width = ((right - left) + static_cast<std::size_t>(1U));
        for (std::size_t offset = 0U; (offset < width); ++offset) {
            std::size_t j = (left + offset);
            ret[top][j] = val;
            val = static_cast<value_type>(val + static_cast<value_type>(1U));
        }
        top = (top + 1U);
        if (top > bottom) {
            break;
        }

        // right column: top -> bottom at current right
        std::size_t height = ((bottom - top) + static_cast<std::size_t>(1U));
        for (std::size_t offset = 0U; (offset < height); ++offset) {
            std::size_t i = (top + offset);
            ret[i][right] = val;
            val = static_cast<value_type>(val + static_cast<value_type>(1U));
        }
        if (right > 0U) {
            right = (right - 1U);
        } else {
            break;
        }
        if (left > right) {
            break;
        }

        // bottom row: right -> left at current bottom
        width = ((right - left) + static_cast<std::size_t>(1U));
        for (std::size_t offset = 0U; (offset < width); ++offset) {
            std::size_t j = (right - offset);
            ret[bottom][j] = val;
            val = static_cast<value_type>(val + static_cast<value_type>(1U));
        }
        if (bottom > 0U) {
            bottom = (bottom - 1U);
        } else {
            break;
        }
        if (top > bottom) {
            break;
        }

        // left column: bottom -> top at current left
        height = ((bottom - top) + static_cast<std::size_t>(1U));
        for (std::size_t offset = 0U; (offset < height); ++offset) {
            std::size_t i = (bottom - offset);
            ret[i][left] = val;
            val = static_cast<value_type>(val + static_cast<value_type>(1U));
        }
        left = (left + 1U);
    }

    return ret;
}
}  // namespace

matrix spiral(std::size_t size) {
    return generate(size);
}

matrix spiral_matrix(std::size_t size) {
    return generate(size);
}

}  // namespace spiral_matrix
