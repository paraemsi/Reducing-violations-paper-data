#include "spiral_matrix.h"

namespace spiral_matrix
{

auto spiral_matrix(value_type size) -> matrix
{
    if (size == 0U)
    {
        return matrix {};
    }

    /* Helper lambda: strict cast from value_type (std::int32_t) → std::size_t.
     * Required because std::vector uses std::size_t for indexing.
     * The cast is a widening, same-signed, integral conversion – allowed.
     */
    auto to_size = [](value_type value) noexcept -> std::size_t
    {
        return static_cast<std::size_t>(value);
    };

    matrix result(
        to_size(size),
        std::vector<value_type>(to_size(size), value_type {0}));

    value_type top {value_type {0}};
    value_type bottom {value_type {size - 1}};
    value_type left {value_type {0}};
    value_type right {value_type {size - 1}};
    value_type count {value_type {1}};

    /* Fill layers moving inward */
    while ((top <= bottom) && (left <= right))
    {
        /* Traverse top row (left → right) */
        for (value_type col {left}; col <= right; ++col)
        {
            result[to_size(top)][to_size(col)] = count;
            ++count;
        }
        ++top;

        /* Traverse right column (top → bottom) */
        for (value_type row {top}; row <= bottom; ++row)
        {
            result[to_size(row)][to_size(right)] = count;
            ++count;
        }
        /* Decrement only when right > 0 to avoid underflow on size == 1 */
        if (right > 0)
        {
            --right;
        }

        /* Traverse bottom row (right → left) */
        if (top <= bottom)
        {
            for (value_type col {right}; col >= left; --col)
            {
                result[to_size(bottom)][to_size(col)] = count;
                ++count;

                if (col == 0)
                {
                    /* Prevent unsigned wraparound */
                    break;
                }
            }
            if (bottom > 0)
            {
                --bottom;
            }
        }

        /* Traverse left column (bottom → top) */
        if (left <= right)
        {
            for (value_type row {bottom}; row >= top; --row)
            {
                result[to_size(row)][to_size(left)] = count;
                ++count;

                if (row == 0)
                {
                    break;
                }
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
