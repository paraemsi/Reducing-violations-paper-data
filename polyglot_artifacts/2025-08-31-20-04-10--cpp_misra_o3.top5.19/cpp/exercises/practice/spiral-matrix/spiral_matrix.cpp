#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size)
{
    if (size <= 0)
    {
        return std::vector<std::vector<int>>{};
    }

    const std::int32_t n { static_cast<std::int32_t>(size) };
    std::vector<std::vector<int>> matrix(
        static_cast<std::size_t>(n),
        std::vector<int>(static_cast<std::size_t>(n), 0));

    std::int32_t top    { 0 };
    std::int32_t bottom { n - 1 };
    std::int32_t left   { 0 };
    std::int32_t right  { n - 1 };

    int value { 1 };

    while ((top <= bottom) && (left <= right))
    {
        for (std::int32_t col { left }; col <= right; ++col)
        {
            matrix[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        for (std::int32_t row { top }; row <= bottom; ++row)
        {
            matrix[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;

        if (top <= bottom)
        {
            for (std::int32_t col { right }; col >= left; --col)
            {
                matrix[static_cast<std::size_t>(bottom)]
                      [static_cast<std::size_t>(col)] = value;
                ++value;
            }
            --bottom;
        }

        if (left <= right)
        {
            for (std::int32_t row { bottom }; row >= top; --row)
            {
                matrix[static_cast<std::size_t>(row)]
                      [static_cast<std::size_t>(left)] = value;
                ++value;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
