#include "queen_attack.h"

#include <stdexcept>    // std::domain_error

namespace queen_attack {

bool chess_board::is_valid(const position_t& pos) noexcept
{
    return ((pos.first >= 0) && (pos.first < 8) &&
            (pos.second >= 0) && (pos.second < 8));
}

chess_board::chess_board(position_t whitePos, position_t blackPos)
    : m_white(whitePos), m_black(blackPos)
{
    if ((m_white == m_black) || (!is_valid(m_white)) || (!is_valid(m_black))) {
        throw std::domain_error("Invalid board position");
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

std::string chess_board::to_string() const
{
    std::string board;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char cell = '_';
            if ((row == m_white.first) && (col == m_white.second)) {
                cell = 'W';
            } else if ((row == m_black.first) && (col == m_black.second)) {
                cell = 'B';
            }
            board += cell;
            if (col < 7) {
                board += ' ';
            }
        }
        if (row < 7) {
            board += '\n';
        }
    }
    return board;
}

chess_board::operator std::string() const
{
    return to_string();
}

bool chess_board::can_attack() const noexcept
{
    bool same_row = (m_white.first == m_black.first);
    bool same_col = (m_white.second == m_black.second);

    int row_diff = (m_white.first - m_black.first);
    int col_diff = (m_white.second - m_black.second);

    int abs_row_diff = ((row_diff < 0) ? (-row_diff) : row_diff);
    int abs_col_diff = ((col_diff < 0) ? (-col_diff) : col_diff);

    bool same_diag = (abs_row_diff == abs_col_diff);

    return (same_row || same_col || same_diag);
}

}  // namespace queen_attack
