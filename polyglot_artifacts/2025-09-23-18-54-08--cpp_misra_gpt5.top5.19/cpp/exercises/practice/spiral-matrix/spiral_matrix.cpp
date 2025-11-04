#include "spiral_matrix.h"

namespace spiral_matrix {

static std::vector<std::vector<int>> spiral(std::size_t dimension)
{
    if ((dimension == static_cast<std::size_t>(0U)))
    {
        return std::vector<std::vector<int>>{};
    }

    const std::size_t n = dimension;
    std::vector<std::vector<int>> matrix(
        n,
        std::vector<int>(n, 0));

    int value = 1;
    const std::size_t layers = ((n + static_cast<std::size_t>(1U)) / static_cast<std::size_t>(2U));

    for (std::size_t layer = static_cast<std::size_t>(0U); layer < layers; ++layer)
    {
        const std::size_t first = layer;
        const std::size_t last = (n - static_cast<std::size_t>(1U)) - layer;

        // Top row: left -> right
        for (std::size_t col = first; col <= last; ++col)
        {
            matrix[first][col] = value;
            value = (value + 1);
        }

        if ((first < last))
        {
            // Right column: top+1 -> bottom
            for (std::size_t row = (first + static_cast<std::size_t>(1U)); row <= last; ++row)
            {
                matrix[row][last] = value;
                value = (value + 1);
            }

            // Bottom row: right-1 -> left
            std::size_t col = last;
            while (col > first)
            {
                col = (col - static_cast<std::size_t>(1U));
                matrix[last][col] = value;
                value = (value + 1);
            }

            // Left column: bottom-1 -> top+1
            std::size_t row = last;
            while (row > (first + static_cast<std::size_t>(1U)))
            {
                row = (row - static_cast<std::size_t>(1U));
                matrix[row][first] = value;
                value = (value + 1);
            }
        }
    }

    return matrix;
}

std::vector<std::vector<int>> spiral_matrix(std::size_t dimension)
{
    return spiral(dimension);
}

}  // namespace spiral_matrix
