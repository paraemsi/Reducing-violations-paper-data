#include "queen_attack.h"

#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(position_type white, position_type black)
    : m_white{white}, m_black{black}
{
    /* Ensure the two queens do not occupy the same position */
    if(white == black)
    {
        throw std::domain_error("Queens cannot share the same position");
    }

    /* Validate that both queens are on the 8 × 8 board */
    const coordinate_type min_coord = static_cast<coordinate_type>(0);
    const coordinate_type max_coord = static_cast<coordinate_type>(7);

    if((white.first < min_coord) || (white.first > max_coord)
       || (white.second < min_coord) || (white.second > max_coord)
       || (black.first < min_coord) || (black.first > max_coord)
       || (black.second < min_coord) || (black.second > max_coord))
    {
        throw std::domain_error("Queen position out of bounds");
    }
}

chess_board::position_type chess_board::white() const noexcept
{
    return m_white;
}

chess_board::position_type chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::same_row(const position_type& lhs,
                           const position_type& rhs) noexcept
{
    return (lhs.first == rhs.first);
}

bool chess_board::same_column(const position_type& lhs,
                              const position_type& rhs) noexcept
{
    return (lhs.second == rhs.second);
}

bool chess_board::same_diagonal(const position_type& lhs,
                                const position_type& rhs) noexcept
{
    const coordinate_type row_diff =
        (lhs.first >= rhs.first) ? (lhs.first - rhs.first)
                                 : (rhs.first - lhs.first);

    const coordinate_type col_diff =
        (lhs.second >= rhs.second) ? (lhs.second - rhs.second)
                                   : (rhs.second - lhs.second);

    return (row_diff == col_diff);
}

bool chess_board::can_attack() const noexcept
{
    return (same_row(m_white, m_black)
            || same_column(m_white, m_black)
            || same_diagonal(m_white, m_black));
}

chess_board::operator std::string() const
{
    std::string board_representation{};
    for(coordinate_type row = static_cast<coordinate_type>(0);
        row < static_cast<coordinate_type>(8);
        ++row)
    {
        for(coordinate_type col = static_cast<coordinate_type>(0);
            col < static_cast<coordinate_type>(8);
            ++col)
        {
            char mark = '_';

            if((row == m_white.first) && (col == m_white.second))
            {
                mark = 'W';
            }
            else if((row == m_black.first) && (col == m_black.second))
            {
                mark = 'B';
            }

            board_representation.push_back(mark);

            if(col < static_cast<coordinate_type>(7))
            {
                board_representation.push_back(' ');
            }
        }

        if(row < static_cast<coordinate_type>(7))
        {
            board_representation.push_back('\n');
        }
    }

    return board_representation;
}

}  // namespace queen_attack
