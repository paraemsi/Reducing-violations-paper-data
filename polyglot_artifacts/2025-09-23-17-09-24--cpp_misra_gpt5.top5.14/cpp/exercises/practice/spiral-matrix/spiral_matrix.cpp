#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix_t
{
    matrix_t matrix{};

    if (size == 0U)
    {
        return matrix;
    }

    matrix = matrix_t(size, std::vector<value_t>(size, static_cast<value_t>(0)));

    std::size_t top = 0U;
    std::size_t bottom = size - 1U;
    std::size_t left = 0U;
    std::size_t right = size - 1U;

    value_t val = static_cast<value_t>(1);

    while ((left <= right) && (top <= bottom))
    {
        for (std::size_t j = left; j <= right; ++j)
        {
            matrix.at(top).at(j) = val;
            ++val;
        }
        ++top;

        for (std::size_t i = top; i <= bottom; ++i)
        {
            matrix.at(i).at(right) = val;
            ++val;
        }
        if (right > 0U)
        {
            --right;
        }

        if (top <= bottom)
        {
            std::size_t j = right;
            while (true)
            {
                matrix.at(bottom).at(j) = val;
                ++val;

                if (j == left)
                {
                    break;
                }
                --j;
            }
            if (bottom > 0U)
            {
                --bottom;
            }
        }

        if ((left <= right) && (top <= bottom))
        {
            std::size_t i = bottom;
            while (true)
            {
                matrix.at(i).at(left) = val;
                ++val;

                if (i == top)
                {
                    break;
                }
                --i;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
