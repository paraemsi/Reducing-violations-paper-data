#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    if (size == 0U)
    {
        return {};
    }

    /* Initialise square matrix filled with zeroes. */
    std::vector<std::vector<std::uint32_t>> matrix(
        static_cast<std::size_t>(size),
        std::vector<std::uint32_t>(static_cast<std::size_t>(size), 0U));

    /* Use signed indices to avoid unsigned wrap-around when
       moving the borders toward the centre. */
    std::int32_t top    = 0;
    std::int32_t bottom = static_cast<std::int32_t>(size) - 1;
    std::int32_t left   = 0;
    std::int32_t right  = static_cast<std::int32_t>(size) - 1;

    std::uint32_t value = 1U;

    while ((top <= bottom) && (left <= right))
    {
        /* Left → right across the current top row */
        for (std::int32_t col = left; col <= right; ++col)
        {
            matrix[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;
        if (top > bottom)
        {
            break;
        }

        /* Top → bottom down the current right column */
        for (std::int32_t row = top; row <= bottom; ++row)
        {
            matrix[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;
        if (left > right)
        {
            break;
        }

        /* Right → left across the current bottom row */
        for (std::int32_t col = right; col >= left; --col)
        {
            matrix[static_cast<std::size_t>(bottom)]
                  [static_cast<std::size_t>(col)] = value;
            ++value;
        }
        --bottom;
        if (top > bottom)
        {
            break;
        }

        /* Bottom → top up the current left column */
        for (std::int32_t row = bottom; row >= top; --row)
        {
            matrix[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(left)] = value;
            ++value;
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
