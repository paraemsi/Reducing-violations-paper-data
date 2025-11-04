#include "queen_attack.h"
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(const position& white, const position& black)
    : m_white(white), m_black(black)
{
    // Check for out-of-bounds
    if ((m_white.first > 7U) || (m_white.second > 7U) ||
        (m_black.first > 7U) || (m_black.second > 7U)) {
        throw std::domain_error("Queen position out of bounds");
    }
    // Check for same position
    if ((m_white.first == m_black.first) && (m_white.second == m_black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position chess_board::white() const
{
    return m_white;
}

position chess_board::black() const
{
    return m_black;
}

bool chess_board::can_attack() const
{
    // Same row
    if (m_white.first == m_black.first) {
        return true;
    }
    // Same column
    if (m_white.second == m_black.second) {
        return true;
    }
    // Same diagonal
    board_index_t row_diff = (m_white.first > m_black.first) ? (m_white.first - m_black.first) : (m_black.first - m_white.first);
    board_index_t col_diff = (m_white.second > m_black.second) ? (m_white.second - m_black.second) : (m_black.second - m_white.second);
    if (row_diff == col_diff) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
