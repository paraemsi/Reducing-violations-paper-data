#include "spiral_matrix.h"

#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size)
{
    if(size == static_cast<std::uint32_t>(0))
    {
        return {};
    }

    std::vector<std::vector<std::uint32_t>> result(
        size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0)));

    std::uint32_t value    = static_cast<std::uint32_t>(1);
    std::uint32_t min_row  = static_cast<std::uint32_t>(0);
    std::uint32_t max_row  = size - static_cast<std::uint32_t>(1);
    std::uint32_t min_col  = static_cast<std::uint32_t>(0);
    std::uint32_t max_col  = size - static_cast<std::uint32_t>(1);

    while((min_row <= max_row) && (min_col <= max_col))
    {
        /* Top row : left → right */
        for(std::uint32_t col = min_col; col <= max_col; ++col)
        {
            result[min_row][col] = value;
            ++value;
        }
        ++min_row;

        /* Right column : top → bottom */
        if(min_row <= max_row)
        {
            for(std::uint32_t row = min_row; row <= max_row; ++row)
            {
                result[row][max_col] = value;
                ++value;
            }
        }
        if(max_col > static_cast<std::uint32_t>(0))
        {
            --max_col;
        }

        /* Bottom row : right → left */
        if(min_row <= max_row)
        {
            for(std::uint32_t col_rev = max_col + static_cast<std::uint32_t>(1);
                (col_rev-- > min_col); )
            {
                result[max_row][col_rev] = value;
                ++value;
            }
            if(max_row > static_cast<std::uint32_t>(0))
            {
                --max_row;
            }
        }

        /* Left column : bottom → top */
        if(min_col <= max_col)
        {
            for(std::uint32_t row_rev = max_row + static_cast<std::uint32_t>(1);
                (row_rev-- > min_row); )
            {
                result[row_rev][min_col] = value;
                ++value;
            }
            ++min_col;
        }
    }

    return result;
}

}  // namespace spiral_matrix
