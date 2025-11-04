#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

auto spiral(std::uint32_t size) -> Matrix
{
    using Index = Matrix::size_type;

    const Index size_idx = static_cast<Index>(size);

    Matrix matrix(size_idx, std::vector<std::uint32_t>(size_idx, 0U));

    if(size == 0U)
    {
        return matrix;
    }

    std::uint32_t value = 1U;
    Index top = 0U;
    Index bottom = size_idx - 1U;
    Index left = 0U;
    Index right = size_idx - 1U;

    while((left <= right) && (top <= bottom))
    {
        for(Index col = left; col <= right; ++col)
        {
            matrix[top][col] = value;
            ++value;
        }
        ++top;
        if(top > bottom)
        {
            break;
        }

        for(Index row = top; row <= bottom; ++row)
        {
            matrix[row][right] = value;
            ++value;
        }
        if(right == 0U)
        {
            break;
        }
        --right;
        if(left > right)
        {
            break;
        }

        {
            Index col = right;
            while(true)
            {
                matrix[bottom][col] = value;
                ++value;
                if(col == left)
                {
                    break;
                }
                --col;
            }
        }
        if(bottom == 0U)
        {
            break;
        }
        --bottom;
        if(top > bottom)
        {
            break;
        }

        {
            Index row = bottom;
            while(true)
            {
                matrix[row][left] = value;
                ++value;
                if(row == top)
                {
                    break;
                }
                --row;
            }
        }
        ++left;
    }

    return matrix;
}

/* Wrapper matching the function name expected by the unit tests */
auto spiral_matrix(std::uint32_t size) -> Matrix
{
    return spiral(size);
}

}  // namespace spiral_matrix
