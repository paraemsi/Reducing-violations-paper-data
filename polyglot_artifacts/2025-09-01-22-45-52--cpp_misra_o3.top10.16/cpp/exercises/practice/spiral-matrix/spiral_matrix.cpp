#include "spiral_matrix.h"

namespace spiral_matrix {

auto generate(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    std::vector<std::vector<std::uint32_t>> matrix{};

    /* A size of zero yields an empty matrix. */
    if(size == static_cast<std::uint32_t>(0U))
    {
        return matrix;
    }

    /* Pre-allocate the square matrix and fill it with zeroes. */
    matrix.resize(
        size,
        std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    /* Define the current outer bounds of the still-to-fill area. */
    std::uint32_t top{static_cast<std::uint32_t>(0U)};
    std::uint32_t bottom{size - static_cast<std::uint32_t>(1U)};
    std::uint32_t left{static_cast<std::uint32_t>(0U)};
    std::uint32_t right{size - static_cast<std::uint32_t>(1U)};

    std::uint32_t value{static_cast<std::uint32_t>(1U)};
    const std::uint32_t limit{size * size};

    /* Walk the perimeter, shrink the bounds, and repeat. */
    while((left <= right) && (top <= bottom))
    {
        /* Top row : left → right. */
        for(std::uint32_t col{left}; col <= right; ++col)
        {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        /* Right column : top → bottom. */
        for(std::uint32_t row{top}; row <= bottom; ++row)
        {
            matrix[row][right] = value;
            ++value;
        }
        if(top > bottom)
        {
            break;
        }
        if(right == static_cast<std::uint32_t>(0U))
        {
            break;
        }
        --right;

        /* Bottom row : right → left (only if rows remain). */
        if(top <= bottom)
        {
            for(std::int32_t col{static_cast<std::int32_t>(right)};
                col >= static_cast<std::int32_t>(left);
                --col)
            {
                matrix[bottom][static_cast<std::uint32_t>(col)] = value;
                ++value;
            }
            --bottom;
        }

        /* Left column : bottom → top (only if columns remain). */
        if(left <= right)
        {
            for(std::int32_t row{static_cast<std::int32_t>(bottom)};
                row >= static_cast<std::int32_t>(top);
                --row)
            {
                matrix[static_cast<std::uint32_t>(row)][left] = value;
                ++value;
            }
            ++left;
        }

        if(value > limit)
        {
            break;
        }
    }

    return matrix;
}

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    return generate(size);
}

}  // namespace spiral_matrix
