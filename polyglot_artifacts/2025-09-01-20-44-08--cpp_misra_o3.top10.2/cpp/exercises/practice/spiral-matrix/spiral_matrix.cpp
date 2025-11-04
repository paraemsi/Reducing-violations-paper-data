#include "spiral_matrix.h"
#include <cstddef>

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size)
{
    if(size == 0U)
    {
        return matrix_t{};
    }

    const std::size_t n = size;
    matrix_t matrix(n, std::vector<value_t>(n, static_cast<value_t>(0U)));

    std::size_t top    = 0U;
    std::size_t bottom = n - 1U;
    std::size_t left   = 0U;
    std::size_t right  = n - 1U;

    value_t current = static_cast<value_t>(1U);

    while((top <= bottom) && (left <= right))
    {
        /* top row (left → right) */
        for(std::size_t col = left; col <= right; ++col)
        {
            matrix[top][col] = current;
            ++current;
        }
        ++top;

        /* right column (top → bottom) */
        for(std::size_t row = top; row <= bottom; ++row)
        {
            matrix[row][right] = current;
            ++current;
        }
        if(right == 0U)
        {
            break;
        }
        --right;

        if(top <= bottom)
        {
            /* bottom row (right → left) */
            for(std::size_t col = right + 1U; (col-- > left);)
            {
                matrix[bottom][col] = current;
                ++current;
            }
            if(bottom == 0U)
            {
                break;
            }
            --bottom;
        }

        if(left <= right)
        {
            /* left column (bottom → top) */
            for(std::size_t row = bottom + 1U; (row-- > top);)
            {
                matrix[row][left] = current;
                ++current;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
