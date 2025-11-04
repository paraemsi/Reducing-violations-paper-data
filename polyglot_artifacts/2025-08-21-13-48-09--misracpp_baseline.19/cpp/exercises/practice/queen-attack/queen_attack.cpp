#include "queen_attack.h"

#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white_pos, const std::pair<int, int>& black_pos)
    : m_white(white_pos), m_black(black_pos)
{
    // Check if positions are on the board
    if (m_white.first < 0 || m_white.first > 7 || m_white.second < 0 || m_white.second > 7 ||
        m_black.first < 0 || m_black.first > 7 || m_black.second < 0 || m_black.second > 7) {
        throw std::domain_error("Queen position must be on a 8x8 board");
    }
    // Check if positions are the same
    if (m_white == m_black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const noexcept {
    return m_white;
}

std::pair<int, int> chess_board::black() const noexcept {
    return m_black;
}

bool chess_board::can_attack() const noexcept {
    int w_col = m_white.first;
    int w_row = m_white.second;
    int b_col = m_black.first;
    int b_row = m_black.second;

    // Same row
    if (w_row == b_row) return true;
    // Same column
    if (w_col == b_col) return true;
    // Same diagonal
    if (std::abs(w_col - b_col) == std::abs(w_row - b_row)) return true;

    return false;
}

}  // namespace queen_attack
