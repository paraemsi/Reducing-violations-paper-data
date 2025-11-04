#include <cstddef>
#include "spiral_matrix.h"

namespace spiral_matrix {

[[nodiscard]] auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    if (size == static_cast<std::uint32_t>(0U)) {
        return matrix_t{};
    }

    matrix_t result(static_cast<std::size_t>(size),
                    std::vector<std::uint32_t>(static_cast<std::size_t>(size),
                                               static_cast<std::uint32_t>(0U)));

    std::int32_t top = 0;
    std::int32_t bottom = static_cast<std::int32_t>(size) - 1;
    std::int32_t left = 0;
    std::int32_t right = static_cast<std::int32_t>(size) - 1;

    std::uint32_t value = static_cast<std::uint32_t>(1U);

    while ((top <= bottom) && (left <= right)) {
        for (std::int32_t col = left; (col <= right); ++col) {
            result.at(static_cast<std::size_t>(top))
                .at(static_cast<std::size_t>(col)) = value;
            ++value;
        }
        ++top;

        for (std::int32_t row = top; (row <= bottom); ++row) {
            result.at(static_cast<std::size_t>(row))
                .at(static_cast<std::size_t>(right)) = value;
            ++value;
        }
        --right;

        if ((top <= bottom) && (left <= right)) {
            for (std::int32_t col = right; (col >= left); --col) {
                result.at(static_cast<std::size_t>(bottom))
                    .at(static_cast<std::size_t>(col)) = value;
                ++value;
            }
            --bottom;

            for (std::int32_t row = bottom; (row >= top); --row) {
                result.at(static_cast<std::size_t>(row))
                    .at(static_cast<std::size_t>(left)) = value;
                ++value;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
