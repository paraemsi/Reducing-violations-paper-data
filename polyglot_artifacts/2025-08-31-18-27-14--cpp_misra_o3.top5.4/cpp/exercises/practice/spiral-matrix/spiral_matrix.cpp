#include "spiral_matrix.h"

#include <vector>
#include <cstdint>
#include <utility>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix
{
    /* Return an empty matrix for the trivial 0-sized request. */
    if(size == static_cast<std::uint32_t>(0U))
    {
        return matrix{};
    }

    /* Initialise a size×size matrix filled with zero. */
    matrix::storage_type data(
        size,
        std::vector<std::int32_t>(size, static_cast<std::int32_t>(0)));

    /* Define the current rectangle borders. */
    std::uint32_t top    = static_cast<std::uint32_t>(0U);
    std::uint32_t bottom = size - static_cast<std::uint32_t>(1U);
    std::uint32_t left   = static_cast<std::uint32_t>(0U);
    std::uint32_t right  = bottom;

    std::int32_t value  = static_cast<std::int32_t>(1);
    const std::int32_t target = static_cast<std::int32_t>(size * size);

    while(value <= target)
    {
        /* Left-to-right along the current top row. */
        for(std::uint32_t col = left; col <= right; ++col)
        {
            data[top][col] = value;
            ++value;
        }
        ++top;
        if(value > target)
        {
            break;
        }

        /* Top-to-bottom along the current right column. */
        for(std::uint32_t row = top; row <= bottom; ++row)
        {
            data[row][right] = value;
            ++value;
        }
        if(right == static_cast<std::uint32_t>(0U))
        {
            break;  /* Prevent unsigned under-flow. */
        }
        --right;
        if(value > target)
        {
            break;
        }

        /* Right-to-left along the current bottom row. */
        for(std::uint32_t col = right; ; --col)
        {
            data[bottom][col] = value;
            ++value;

            if(col == left)
            {
                break;
            }
        }
        if(bottom == static_cast<std::uint32_t>(0U))
        {
            break;
        }
        --bottom;
        if(value > target)
        {
            break;
        }

        /* Bottom-to-top along the current left column. */
        for(std::uint32_t row = bottom; ; --row)
        {
            data[row][left] = value;
            ++value;

            if(row == top)
            {
                break;
            }
        }
        ++left;
    }

    return matrix{std::move(data)};
}

}  // namespace spiral_matrix
