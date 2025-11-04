#include "queen_attack.h"

#include <cstddef>
#include <stdexcept>

namespace queen_attack {

using detail::board_pos_t;
constexpr board_pos_t board_size{detail::board_size};

static void validate_position(const chess_board::position_t& pos)
{
    /*  Accepts signed coordinates; values must be within [0, board_size-1]  */
    if ((pos.first < 0) || (pos.second < 0) ||
        (pos.first >= static_cast<std::int32_t>(board_size)) ||
        (pos.second >= static_cast<std::int32_t>(board_size)))
    {
        throw std::domain_error("Queen position out of range");
    }
}

chess_board::chess_board(position_t white_pos, position_t black_pos)
    : m_white{white_pos}, m_black{black_pos}
{
    validate_position(m_white);
    validate_position(m_black);

    if ((m_white.first == m_black.first) && (m_white.second == m_black.second))
    {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

chess_board::position_t chess_board::white() const noexcept
{
    return m_white;
}

chess_board::position_t chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    /* same rank or same file */
    bool same_row{m_white.first == m_black.first};
    bool same_col{m_white.second == m_black.second};

    /* absolute distance along both axes */
    std::int32_t row_diff{
        (m_white.first >= m_black.first) ? (m_white.first - m_black.first)
                                         : (m_black.first - m_white.first)};
    std::int32_t col_diff{
        (m_white.second >= m_black.second) ? (m_white.second - m_black.second)
                                           : (m_black.second - m_white.second)};

    bool same_diag{row_diff == col_diff};

    return (same_row || same_col) || same_diag;
}

chess_board::operator std::string() const
{
    std::string board{};
    board.reserve(static_cast<std::size_t>(board_size) *
                  static_cast<std::size_t>(board_size) * 2U);

    for (board_pos_t row{0U}; row < board_size; ++row)
    {
        for (board_pos_t col{0U}; col < board_size; ++col)
        {
            char cell{'_'};
            if ((static_cast<std::int32_t>(row) == m_white.first) &&
                (static_cast<std::int32_t>(col) == m_white.second))
            {
                cell = 'W';
            }
            else if ((static_cast<std::int32_t>(row) == m_black.first) &&
                     (static_cast<std::int32_t>(col) == m_black.second))
            {
                cell = 'B';
            }

            board.push_back(cell);

            if (col < static_cast<board_pos_t>(board_size - static_cast<board_pos_t>(1U)))
            {
                board.push_back(' ');
            }
        }

        if (row < static_cast<board_pos_t>(board_size - static_cast<board_pos_t>(1U)))
        {
            board.push_back('\n');
        }
    }

    return board;
}

}  // namespace queen_attack
