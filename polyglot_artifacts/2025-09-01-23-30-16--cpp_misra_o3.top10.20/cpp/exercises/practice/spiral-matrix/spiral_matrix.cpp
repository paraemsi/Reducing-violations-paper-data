#include "spiral_matrix.h"

#include <cstddef>   //  for std::size_t

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    if(size == 0U)
    {
        return matrix_t{};
    }

    const std::int32_t n = static_cast<std::int32_t>(size);

    matrix_t matrix(
        static_cast<std::size_t>(size),
        std::vector<std::int32_t>(static_cast<std::size_t>(size), 0));

    std::int32_t value = 1;
    std::int32_t  top     = 0;
    std::int32_t  bottom  = n - 1;
    std::int32_t  left    = 0;
    std::int32_t  right   = n - 1;

    while(((top <= bottom) && (left <= right)))
    {
        //  left → right along the current top row
        for(std::int32_t col = left; col <= right; ++col)
        {
            matrix[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        //  top ↓ bottom along the current rightmost column
        for(std::int32_t row = top; row <= bottom; ++row)
        {
            matrix[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;

        if((top > bottom) || (left > right))
        {
            break;
        }

        //  right → left along the current bottom row
        for(std::int32_t col = right; col >= left; --col)
        {
            matrix[static_cast<std::size_t>(bottom)]
                  [static_cast<std::size_t>(col)] = value;
            ++value;
        }
        --bottom;

        //  bottom ↑ top along the current leftmost column
        for(std::int32_t row = bottom; row >= top; --row)
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
