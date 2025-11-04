#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size)
{
    if(size == 0U)
    {
        return {};
    }

    matrix_t matrix(static_cast<std::size_t>(size),
                    std::vector<value_t>(static_cast<std::size_t>(size), 0));

    value_t current { 1 };

    std::int32_t top { 0 };
    std::int32_t bottom { static_cast<std::int32_t>(size) - 1 };
    std::int32_t left   { 0 };
    std::int32_t right  { static_cast<std::int32_t>(size) - 1 };

    while((top <= bottom) && (left <= right))
    {
        for(std::int32_t col { left }; col <= right; ++col)
        {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = current;
            ++current;
        }
        ++top;

        for(std::int32_t row { top }; row <= bottom; ++row)
        {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = current;
            ++current;
        }
        --right;

        if((top <= bottom) && (left <= right))
        {
            for(std::int32_t col { right }; col >= left; --col)
            {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = current;
                ++current;
            }
            --bottom;

            for(std::int32_t row { bottom }; row >= top; --row)
            {
                matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = current;
                ++current;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
