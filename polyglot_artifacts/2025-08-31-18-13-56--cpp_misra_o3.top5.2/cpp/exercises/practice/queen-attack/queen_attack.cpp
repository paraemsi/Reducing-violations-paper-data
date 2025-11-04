#include "queen_attack.h"

#include <cmath>
#include <stdexcept>
#include <sstream>

namespace queen_attack {

bool chess_board::is_valid(const std::pair<index_t, index_t>& pos) noexcept
{
    return ((pos.first >= static_cast<index_t>(0)) &&
            (pos.first < board_size) &&
            (pos.second >= static_cast<index_t>(0)) &&
            (pos.second < board_size));
}

chess_board::chess_board(std::pair<index_t, index_t> white_pos,
                         std::pair<index_t, index_t> black_pos) :
    m_white{white_pos},
    m_black{black_pos}
{
    if((m_white == m_black) || (!is_valid(m_white)) || (!is_valid(m_black)))
    {
        throw std::domain_error("Invalid queen position");
    }
}

std::pair<index_t, index_t> chess_board::white() const noexcept
{
    return m_white;
}

std::pair<index_t, index_t> chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row{(m_white.second == m_black.second)};
    const bool same_col{(m_white.first == m_black.first)};
    const bool same_diag{(std::abs(m_white.first - m_black.first) ==
                           std::abs(m_white.second - m_black.second))};

    return (same_row || same_col || same_diag);
}

chess_board::operator std::string() const
{
    std::ostringstream board_stream;

    for(index_t row{0}; row < board_size; ++row)
    {
        for(index_t col{0}; col < board_size; ++col)
        {
            char symbol{'_'};

            if((m_white.first == col) && (m_white.second == row))
            {
                symbol = 'W';
            }
            else if((m_black.first == col) && (m_black.second == row))
            {
                symbol = 'B';
            }

            board_stream << symbol;

            if(col < (board_size - static_cast<index_t>(1)))
            {
                board_stream << ' ';
            }
        }
        board_stream << '\n';
    }

    return board_stream.str();
}

}  // namespace queen_attack
