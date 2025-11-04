#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix_type
{
    matrix_type matrix;

    if (size == 0U)
    {
        return matrix; /* Return an empty matrix */
    }

    /* Initialise an empty size × size matrix filled with zeroes */
    matrix.assign(size, std::vector<std::uint32_t>(size, 0U));

    std::uint32_t top    = 0U;
    std::uint32_t bottom = size - 1U;
    std::uint32_t left   = 0U;
    std::uint32_t right  = size - 1U;

    std::uint32_t value  = 1U;

    while ((left <= right) && (top <= bottom))
    {
        /* Traverse left → right across the current top row */
        for (std::uint32_t col = left; col <= right; ++col)
        {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        /* Traverse top → bottom down the current rightmost column */
        for (std::uint32_t row = top; row <= bottom; ++row)
        {
            matrix[row][right] = value;
            ++value;
        }
        if (right == 0U)
        {
            break; /* Prevent unsigned underflow */
        }
        --right;

        /* Traverse right → left across the current bottom row, if any rows remain */
        if (top <= bottom)
        {
            for (std::int32_t col = static_cast<std::int32_t>(right);
                 col >= static_cast<std::int32_t>(left);
                 --col)
            {
                matrix[bottom][static_cast<std::uint32_t>(col)] = value;
                ++value;
            }
            if (bottom == 0U)
            {
                break; /* Prevent unsigned underflow */
            }
            --bottom;
        }

        /* Traverse bottom → top up the current leftmost column, if any columns remain */
        if (left <= right)
        {
            for (std::int32_t row = static_cast<std::int32_t>(bottom);
                 row >= static_cast<std::int32_t>(top);
                 --row)
            {
                matrix[static_cast<std::uint32_t>(row)][left] = value;
                ++value;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
