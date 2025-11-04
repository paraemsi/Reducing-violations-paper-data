#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> Matrix
{
    /* Handle the 0 × 0 matrix case immediately. */
    if(size == 0U)
    {
        return {};
    }

    Matrix matrix(size, std::vector<std::uint32_t>(size, 0U));

    /* Define the current bounds of the yet-to-be-filled rectangle. */
    std::uint32_t left   = 0U;
    std::uint32_t right  = size - 1U;
    std::uint32_t top    = 0U;
    std::uint32_t bottom = size - 1U;

    std::uint32_t value = 1U;

    while((left <= right) && (top <= bottom))
    {
        /* ---- Traverse from left → right along the top row. ---- */
        for(std::uint32_t col = left; col <= right; ++col)
        {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        /* ---- Traverse from top → bottom along the right column. ---- */
        for(std::uint32_t row = top; row <= bottom; ++row)
        {
            matrix[row][right] = value;
            ++value;
        }
        if(right == 0U) /* Prevent unsigned wrap-around before decrement. */
        {
            break;
        }
        --right;

        /* ---- Traverse from right → left along the bottom row. ---- */
        if(top <= bottom)
        {
            for(std::uint32_t col = right; /* no condition */ ; --col)
            {
                matrix[bottom][col] = value;
                ++value;
                if(col == left)
                {
                    break;
                }
            }
            if(bottom == 0U)
            {
                break;
            }
            --bottom;
        }

        /* ---- Traverse from bottom → top along the left column. ---- */
        if(left <= right)
        {
            for(std::uint32_t row = bottom; /* no condition */ ; --row)
            {
                matrix[row][left] = value;
                ++value;
                if(row == top)
                {
                    break;
                }
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
