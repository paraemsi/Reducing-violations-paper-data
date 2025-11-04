#include "spiral_matrix.h"

#include <cstddef>   // for std::size_t
#include <cstdint>   // for fixed-width integer types

namespace spiral_matrix {

matrix_t spiral_matrix(std::uint32_t size)
{
    if(size == static_cast<std::uint32_t>(0U))
    {
        return matrix_t{};
    }

    const std::size_t n = static_cast<std::size_t>(size);  /* explicit cast to satisfy std::vector */
    matrix_t result(
        n,
        std::vector<std::uint32_t>(n, static_cast<std::uint32_t>(0U)));

    std::size_t top    = static_cast<std::size_t>(0U);
    std::size_t bottom = n - static_cast<std::size_t>(1U);
    std::size_t left   = static_cast<std::size_t>(0U);
    std::size_t right  = n - static_cast<std::size_t>(1U);

    std::uint32_t value = static_cast<std::uint32_t>(1U);

    while((top <= bottom) && (left <= right))
    {
        /* traverse top row: left → right */
        for(std::size_t col = left; col <= right; ++col)
        {
            result[top][col] = value;
            ++value;
        }
        ++top;

        /* traverse right column: top → bottom */
        for(std::size_t row = top; row <= bottom; ++row)
        {
            result[row][right] = value;
            ++value;
        }

        if(left == right)
        {
            break; /* completed central column */
        }
        --right;

        /* traverse bottom row: right → left */
        for(std::int64_t col = static_cast<std::int64_t>(right);
            col >= static_cast<std::int64_t>(left);
            --col)
        {
            result[bottom][static_cast<std::size_t>(col)] = value;
            ++value;
        }

        if(top == bottom)
        {
            break; /* completed central row */
        }
        --bottom;

        /* traverse left column: bottom → top */
        for(std::int64_t row = static_cast<std::int64_t>(bottom);
            row >= static_cast<std::int64_t>(top);
            --row)
        {
            result[static_cast<std::size_t>(row)][left] = value;
            ++value;
        }
        ++left;
    }

    return result;
}

}  // namespace spiral_matrix
