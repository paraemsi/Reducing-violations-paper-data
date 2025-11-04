#include "queen_attack.h"

#include <ostream>
#include <sstream>
#include <stdexcept>

namespace queen_attack
{

namespace
{
constexpr coordinate_t board_size = static_cast<coordinate_t>(8);
} // unnamed namespace

void chess_board::validate_position(const position_t& pos)
{
    const bool row_valid = (pos.first >= static_cast<coordinate_t>(0)) &&
                           (pos.first < board_size);
    const bool col_valid = (pos.second >= static_cast<coordinate_t>(0)) &&
                           (pos.second < board_size);

    if (!(row_valid && col_valid))
    {
        throw std::domain_error("Invalid position");
    }
}

chess_board::chess_board(const position_t white_pos, const position_t black_pos) :
    m_white{white_pos},
    m_black{black_pos}
{
    validate_position(m_white);
    validate_position(m_black);

    if ((m_white == m_black))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position_t chess_board::white() const noexcept
{
    return m_white;
}

position_t chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row = (m_white.first == m_black.first);
    const bool same_col = (m_white.second == m_black.second);

    const coordinate_t row_diff = (m_white.first > m_black.first) ?
                                  (m_white.first - m_black.first) :
                                  (m_black.first - m_white.first);
    const coordinate_t col_diff = (m_white.second > m_black.second) ?
                                  (m_white.second - m_black.second) :
                                  (m_black.second - m_white.second);

    const bool same_diag = (row_diff == col_diff);

    return (same_row || same_col) || same_diag;
}

chess_board::operator std::string() const
{
    std::ostringstream oss;

    for (coordinate_t row = static_cast<coordinate_t>(0); row < board_size; ++row)
    {
        for (coordinate_t col = static_cast<coordinate_t>(0); col < board_size; ++col)
        {
            char square = '_';

            if ((row == m_white.first) && (col == m_white.second))
            {
                square = 'W';
            }
            else if ((row == m_black.first) && (col == m_black.second))
            {
                square = 'B';
            }

            oss << square;

            if (col < (board_size - static_cast<coordinate_t>(1)))
            {
                oss << ' ';
            }
        }

        if (row < (board_size - static_cast<coordinate_t>(1)))
        {
            oss << '\n';
        }
    }

    return oss.str();
}

} // namespace queen_attack
