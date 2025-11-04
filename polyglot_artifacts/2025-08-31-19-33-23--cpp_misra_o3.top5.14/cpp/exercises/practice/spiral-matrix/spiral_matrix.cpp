#include "spiral_matrix.h"

#include <cstdint>
#include <vector>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    matrix_t result{};

    if(size == static_cast<std::uint32_t>(0U))
    {
        return result;
    }

    /* Create a size × size matrix initialised with 0 */
    result.assign(size, std::vector<element_t>(size, static_cast<element_t>(0)));

    std::uint32_t top{static_cast<std::uint32_t>(0U)};
    std::uint32_t left{static_cast<std::uint32_t>(0U)};
    std::uint32_t bottom{size - static_cast<std::uint32_t>(1U)};
    std::uint32_t right{size - static_cast<std::uint32_t>(1U)};

    element_t current{static_cast<element_t>(1)};

    while((top <= bottom) && (left <= right))
    {
        /* Traverse from left to right along the current top row */
        for(std::uint32_t col = left; col <= right; ++col)
        {
            result[top][col] = current;
            ++current;
        }
        ++top;

        /* Traverse from top to bottom along the current right column */
        for(std::uint32_t row = top; row <= bottom; ++row)
        {
            result[row][right] = current;
            ++current;
        }
        if(right == static_cast<std::uint32_t>(0U))
        {
            /* Prevent underflow if size == 1 */
            break;
        }
        --right;

        /* Traverse from right to left along the current bottom row */
        if(top <= bottom)
        {
            for(std::uint32_t col = right + static_cast<std::uint32_t>(1U); col-- > left; )
            {
                result[bottom][col] = current;
                ++current;
            }
            if(bottom == static_cast<std::uint32_t>(0U))
            {
                break;
            }
            --bottom;
        }

        /* Traverse from bottom to top along the current left column */
        if(left <= right)
        {
            for(std::uint32_t row = bottom + static_cast<std::uint32_t>(1U); row-- > top; )
            {
                result[row][left] = current;
                ++current;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
