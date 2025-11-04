#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix_type
{
    if (size == static_cast<std::size_t>(0U))
    {
        return matrix_type{};
    }

    const std::size_t n = size;
    matrix_type result(n, std::vector<value_type>(n, static_cast<value_type>(0U)));

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t bottom = static_cast<std::size_t>(n - static_cast<std::size_t>(1U));
    std::size_t right = static_cast<std::size_t>(n - static_cast<std::size_t>(1U));

    value_type num = static_cast<value_type>(1U);

    while ((left <= right) && (top <= bottom))
    {
        for (std::size_t c = left; c <= right; c = static_cast<std::size_t>(c + static_cast<std::size_t>(1U)))
        {
            result[top][c] = num;
            num = static_cast<value_type>(num + static_cast<value_type>(1U));
        }
        top = static_cast<std::size_t>(top + static_cast<std::size_t>(1U));

        for (std::size_t r = top; r <= bottom; r = static_cast<std::size_t>(r + static_cast<std::size_t>(1U)))
        {
            result[r][right] = num;
            num = static_cast<value_type>(num + static_cast<value_type>(1U));
        }
        if (right > static_cast<std::size_t>(0U))
        {
            right = static_cast<std::size_t>(right - static_cast<std::size_t>(1U));
        }
        else
        {
            right = static_cast<std::size_t>(0U);
        }

        if ((top <= bottom) && (left <= right))
        {
            for (std::size_t c = left; c <= right; c = static_cast<std::size_t>(c + static_cast<std::size_t>(1U)))
            {
                const std::size_t col = static_cast<std::size_t>(right - (c - left));
                result[bottom][col] = num;
                num = static_cast<value_type>(num + static_cast<value_type>(1U));
            }
            if (bottom > static_cast<std::size_t>(0U))
            {
                bottom = static_cast<std::size_t>(bottom - static_cast<std::size_t>(1U));
            }
            else
            {
                bottom = static_cast<std::size_t>(0U);
            }
        }

        if ((left <= right) && (top <= bottom))
        {
            for (std::size_t r = top; r <= bottom; r = static_cast<std::size_t>(r + static_cast<std::size_t>(1U)))
            {
                const std::size_t row = static_cast<std::size_t>(bottom - (r - top));
                result[row][left] = num;
                num = static_cast<value_type>(num + static_cast<value_type>(1U));
            }
            left = static_cast<std::size_t>(left + static_cast<std::size_t>(1U));
        }
    }

    return result;
}

}  // namespace spiral_matrix
