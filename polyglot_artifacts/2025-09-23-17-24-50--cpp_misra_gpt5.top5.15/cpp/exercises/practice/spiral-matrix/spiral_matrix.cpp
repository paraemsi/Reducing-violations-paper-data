#include "spiral_matrix.h"

namespace {

spiral_matrix::matrix_t build_spiral(std::size_t size) {
    spiral_matrix::matrix_t mat(size, std::vector<std::int32_t>(size, static_cast<std::int32_t>(0)));

    if (size == static_cast<std::size_t>(0U)) {
        return mat;
    } else {
        // proceed with filling
    }

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t bottom = (size - static_cast<std::size_t>(1U));
    std::size_t right = (size - static_cast<std::size_t>(1U));

    std::int32_t val = static_cast<std::int32_t>(1);

    while ((top <= bottom) && (left <= right)) {
        // top row: left -> right
        for (std::size_t j = left; j <= right; ++j) {
            mat.at(top).at(j) = val;
            val = (val + static_cast<std::int32_t>(1));
        }

        // right column: top+1 -> bottom
        if (top < bottom) {
            for (std::size_t i = (top + static_cast<std::size_t>(1U)); i <= bottom; ++i) {
                mat.at(i).at(right) = val;
                val = (val + static_cast<std::int32_t>(1));
            }
        } else {
            // single row handled above
        }

        // bottom row: right-1 -> left
        if ((left < right) && (top < bottom)) {
            std::size_t j = (right - static_cast<std::size_t>(1U));
            while (true) {
                mat.at(bottom).at(j) = val;
                val = (val + static_cast<std::int32_t>(1));
                if (j == left) {
                    break;
                } else {
                    j = (j - static_cast<std::size_t>(1U));
                }
            }
        } else {
            // no distinct bottom row to process
        }

        // left column: bottom-1 -> top+1
        if ((left < right) && ((top + static_cast<std::size_t>(1U)) < bottom)) {
            std::size_t i = (bottom - static_cast<std::size_t>(1U));
            while (true) {
                mat.at(i).at(left) = val;
                val = (val + static_cast<std::int32_t>(1));
                if (i == (top + static_cast<std::size_t>(1U))) {
                    break;
                } else {
                    i = (i - static_cast<std::size_t>(1U));
                }
            }
        } else {
            // no distinct left column to process
        }

        top = (top + static_cast<std::size_t>(1U));
        left = (left + static_cast<std::size_t>(1U));
        if (bottom > static_cast<std::size_t>(0U)) {
            bottom = (bottom - static_cast<std::size_t>(1U));
        } else {
            // already at zero
        }
        if (right > static_cast<std::size_t>(0U)) {
            right = (right - static_cast<std::size_t>(1U));
        } else {
            // already at zero
        }
    }

    return mat;
}

}  // namespace

namespace spiral_matrix {

matrix_t spiral(const std::size_t size) {
    return build_spiral(size);
}

matrix_t spiral_matrix(const std::size_t size) {
    return build_spiral(size);
}

matrix_t generate(const std::size_t size) {
    return build_spiral(size);
}

}  // namespace spiral_matrix
