#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    /* handle the degenerate case of a 0 × 0 matrix */
    if (size == 0U)
    {
        return matrix_t {};
    }

    /* create size×size matrix initialised to zero */
    matrix_t matrix(size, std::vector<std::uint32_t>(size, 0U));

    /* boundaries of the current “ring” */
    std::uint32_t top {0U};
    std::uint32_t bottom {(size - 1U)};
    std::uint32_t left {0U};
    std::uint32_t right {(size - 1U)};

    std::uint32_t value {1U};

    while ((left <= right) && (top <= bottom))
    {
        /* move left → right across the top row */
        for (std::uint32_t col {left}; col <= right; ++col)
        {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        /* move top → bottom down the rightmost column */
        for (std::uint32_t row {top}; row <= bottom; ++row)
        {
            matrix[row][right] = value;
            ++value;
        }
        if (right == 0U)
        {
            break; /* avoid under-flow before decrementing */
        }
        --right;

        /* move right → left across the bottom row (if any rows remain) */
        if (top <= bottom)
        {
            for (std::uint32_t col {right + 1U}; col-- > left; )
            {
                matrix[bottom][col] = value;
                ++value;
            }
            if (bottom == 0U)
            {
                break;
            }
            --bottom;
        }

        /* move bottom → top up the leftmost column (if any columns remain) */
        if (left <= right)
        {
            for (std::uint32_t row {bottom + 1U}; row-- > top; )
            {
                matrix[row][left] = value;
                ++value;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
