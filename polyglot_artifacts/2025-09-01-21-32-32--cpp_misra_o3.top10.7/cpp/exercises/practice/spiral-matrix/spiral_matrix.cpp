#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> Matrix
{
    /* Guard: zero-sized request yields an empty matrix */
    if(size == static_cast<std::uint32_t>(0))
    {
        return Matrix{};
    }

    Matrix result(size, std::vector<Element>(size, static_cast<Element>(0)));

    std::uint32_t left   = static_cast<std::uint32_t>(0);
    std::uint32_t right  = size - static_cast<std::uint32_t>(1);
    std::uint32_t top    = static_cast<std::uint32_t>(0);
    std::uint32_t bottom = size - static_cast<std::uint32_t>(1);

    Element value  = static_cast<Element>(1);

    while((left <= right) && (top <= bottom))
    {
        /* Traverse from left → right along the current top row */
        for(std::uint32_t col = left; col <= right; ++col)
        {
            result[top][col] = value;
            ++value;
        }
        ++top;

        /* Traverse from top → bottom along the current right column */
        if(top <= bottom)
        {
            for(std::uint32_t row = top; row <= bottom; ++row)
            {
                result[row][right] = value;
                ++value;
            }
        }
        if(right > static_cast<std::uint32_t>(0))
        {
            --right;
        }

        /* Traverse from right → left along the current bottom row */
        if((top <= bottom) && (left <= right))
        {
            for(std::uint32_t col = right; /* condition handled inside */ ; --col)
            {
                result[bottom][col] = value;
                ++value;
                if(col == left)
                {
                    break;
                }
            }
            if(bottom > static_cast<std::uint32_t>(0))
            {
                --bottom;
            }
        }

        /* Traverse from bottom → top along the current left column */
        if((left <= right) && (top <= bottom))
        {
            for(std::uint32_t row = bottom; /* condition handled inside */ ; --row)
            {
                result[row][left] = value;
                ++value;
                if(row == top)
                {
                    break;
                }
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
