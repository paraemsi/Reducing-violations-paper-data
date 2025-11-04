#include "spiral_matrix.h"

namespace spiral_matrix {

/**
 * @brief Construct a clockwise spiral matrix.
 *
 * The matrix is filled with consecutive natural numbers starting
 * from 1 in the top-left corner, proceeding clockwise toward the centre.
 */
auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    std::vector<std::vector<std::uint32_t>> matrix{};

    if (size == static_cast<std::uint32_t>(0U))
    {
        return matrix;
    }

    matrix.assign(size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    std::uint32_t top{static_cast<std::uint32_t>(0U)};
    std::uint32_t bottom{static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U))};
    std::uint32_t left{static_cast<std::uint32_t>(0U)};
    std::uint32_t right{static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U))};

    std::uint32_t value{static_cast<std::uint32_t>(1U)};
    const std::uint32_t max_value{static_cast<std::uint32_t>(size * size)};

    while (value <= max_value)
    {
        /* Fill the current top row (left → right) */
        for (std::uint32_t col{left}; col <= right; ++col)
        {
            matrix[top][col] = value;
            ++value;
        }
        ++top;
        if (top > bottom)
        {
            break;
        }

        /* Fill the current right column (top → bottom) */
        for (std::uint32_t row{top}; row <= bottom; ++row)
        {
            matrix[row][right] = value;
            ++value;
        }
        if (right == static_cast<std::uint32_t>(0U))
        {
            break; /* Prevent unsigned underflow */
        }
        --right;
        if (left > right)
        {
            break;
        }

        /* Fill the current bottom row (right → left) */
        for (std::uint32_t col{right + static_cast<std::uint32_t>(1U)}; (col--) > left; )
        {
            matrix[bottom][col] = value;
            ++value;
            if (col == left)
            {
                break;
            }
        }
        if (bottom == static_cast<std::uint32_t>(0U))
        {
            break; /* Prevent unsigned underflow */
        }
        --bottom;
        if (top > bottom)
        {
            break;
        }

        /* Fill the current left column (bottom → top) */
        for (std::uint32_t row{bottom + static_cast<std::uint32_t>(1U)}; (row--) > top; )
        {
            matrix[row][left] = value;
            ++value;
            if (row == top)
            {
                break;
            }
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
