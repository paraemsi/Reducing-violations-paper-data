#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    std::vector<std::vector<std::uint32_t>> matrix {};

    if(size == static_cast<std::uint32_t>(0U))
    {
        return matrix; /* Return empty matrix for size 0 */
    }

    /* Initialise matrix with zeros */
    matrix.assign(
        size,
        std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    /* Define the current perimeter */
    std::uint32_t top { static_cast<std::uint32_t>(0U) };
    std::uint32_t bottom { static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U)) };
    std::uint32_t left { static_cast<std::uint32_t>(0U) };
    std::uint32_t right { static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U)) };

    /* Current value to write */
    std::uint32_t current { static_cast<std::uint32_t>(1U) };

    /* Total number of cells, kept in 64-bit to avoid overflow for large size */
    const std::uint64_t total {
        static_cast<std::uint64_t>(size) * static_cast<std::uint64_t>(size)
    };

    /* Fill the matrix layer by layer */
    while(true)
    {
        /* Traverse from left to right */
        for(std::uint32_t col { left }; col <= right; ++col)
        {
            matrix[top][col] = current;
            ++current;
        }

        if(static_cast<std::uint64_t>(current) > total)
        {
            break;
        }

        ++top;

        /* Traverse from top to bottom */
        for(std::uint32_t row { top }; row <= bottom; ++row)
        {
            matrix[row][right] = current;
            ++current;
        }

        if(static_cast<std::uint64_t>(current) > total)
        {
            break;
        }

        if(right == static_cast<std::uint32_t>(0U))
        {
            break; /* Prevent unsigned underflow */
        }
        --right;

        /* Traverse from right to left */
        for(std::uint32_t col_r { right }; col_r >= left; --col_r)
        {
            matrix[bottom][col_r] = current;
            ++current;

            if(col_r == static_cast<std::uint32_t>(0U))
            {
                break; /* Prevent unsigned underflow */
            }
        }

        if(static_cast<std::uint64_t>(current) > total)
        {
            break;
        }

        if(bottom == static_cast<std::uint32_t>(0U))
        {
            break;
        }
        --bottom;

        /* Traverse from bottom to top */
        for(std::uint32_t row_r { bottom }; row_r >= top; --row_r)
        {
            matrix[row_r][left] = current;
            ++current;

            if(row_r == static_cast<std::uint32_t>(0U))
            {
                break; /* Prevent unsigned underflow */
            }
        }

        if(static_cast<std::uint64_t>(current) > total)
        {
            break;
        }

        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
