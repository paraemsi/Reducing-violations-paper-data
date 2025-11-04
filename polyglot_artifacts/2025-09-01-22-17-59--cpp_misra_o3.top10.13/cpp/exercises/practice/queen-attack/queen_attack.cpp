#include "queen_attack.h"

#include <stdexcept>
#include <ostream>
#include <cstdlib>   // for std::abs

namespace queen_attack {

chess_board::chess_board(const position_type& white_pos,
                         const position_type& black_pos)
    : m_white{white_pos},
      m_black{black_pos}
{
    const coordinate_type max_index = static_cast<coordinate_type>(7U);

    if ((m_white.first > max_index) || (m_white.second > max_index) ||
        (m_black.first > max_index) || (m_black.second > max_index))
    {
        throw std::domain_error("Queen position out of bounds");
    }

    if ((m_white.first == m_black.first) &&
        (m_white.second == m_black.second))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position_type chess_board::white() const noexcept
{
    return m_white;
}

position_type chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    if (m_white.first == m_black.first)
    {
        return true;
    }

    if (m_white.second == m_black.second)
    {
        return true;
    }

    const coordinate_type delta_x = m_white.first - m_black.first;
    const coordinate_type delta_y = m_white.second - m_black.second;

    return (std::abs(delta_x) == std::abs(delta_y));
}

std::ostream& operator<<(std::ostream& os, const chess_board& board)
{
    for (coordinate_type row = static_cast<coordinate_type>(0U);
         row < static_cast<coordinate_type>(8U);
         ++row)
    {
        for (coordinate_type col = static_cast<coordinate_type>(0U);
             col < static_cast<coordinate_type>(8U);
             ++col)
        {
            if ((board.white().first == col) &&
                (board.white().second == row))
            {
                os << 'W';
            }
            else if ((board.black().first == col) &&
                     (board.black().second == row))
            {
                os << 'B';
            }
            else
            {
                os << '_';
            }

            if (col < static_cast<coordinate_type>(7U))
            {
                os << ' ';
            }
        }

        if (row < static_cast<coordinate_type>(7U))
        {
            os << '\n';
        }
    }
    return os;
}

}  // namespace queen_attack
