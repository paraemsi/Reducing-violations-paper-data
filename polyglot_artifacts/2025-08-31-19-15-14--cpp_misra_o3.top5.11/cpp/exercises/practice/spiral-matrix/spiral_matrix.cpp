#include "spiral_matrix.h"

#include <cstddef>

namespace spiral_matrix {

matrix_t spiral_matrix(std::uint32_t size)
{
    /* Guard against zero-sized request to prevent underflow on (size - 1U). */
    if (size == 0U)
    {
        return matrix_t{};
    }

    matrix_t matrix(size, std::vector<std::uint32_t>(size, 0U));

    std::uint32_t top = 0U;
    std::uint32_t bottom = static_cast<std::uint32_t>(size - 1U);
    std::uint32_t left = 0U;
    std::uint32_t right = static_cast<std::uint32_t>(size - 1U);

    std::uint32_t value = 1U;

    while (value <= (size * size))
    {
        /* Fill the top row */
        for (std::uint32_t col = left; col <= right; ++col)
        {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        if (top > bottom)
        {
            break;
        }

        /* Fill the right column */
        for (std::uint32_t row = top; row <= bottom; ++row)
        {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        if (right == 0U)
        {
            break;
        }
        --right;

        if (left > right)
        {
            break;
        }

        /* Fill the bottom row */
        for (std::uint32_t col = right; (col + 1U) > left; --col)
        {
            matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
            ++value;
            if (col == left)
            {
                break;
            }
        }
        if (bottom == 0U)
        {
            break;
        }
        --bottom;

        if (top > bottom)
        {
            break;
        }

        /* Fill the left column */
        for (std::uint32_t row = bottom; (row + 1U) > top; --row)
        {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
            ++value;
            if (row == top)
            {
                break;
            }
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
