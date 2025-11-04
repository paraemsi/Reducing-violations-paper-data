#include "queen_attack.h"

#include <cmath>

namespace queen_attack {

bool chess_board::on_board(const std::pair<int,int>& pos) noexcept {
    return pos.first >= 0 && pos.first < 8 &&
           pos.second >= 0 && pos.second < 8;
}

chess_board::chess_board(std::pair<int,int> white, std::pair<int,int> black)
    : m_white{white}, m_black{black} {
    if (!on_board(m_white) || !on_board(m_black) || m_white == m_black) {
        throw std::domain_error("Invalid board positions");
    }
}

std::pair<int,int> chess_board::white() const noexcept {
    return m_white;
}

std::pair<int,int> chess_board::black() const noexcept {
    return m_black;
}

bool chess_board::can_attack() const noexcept {
    // same row
    if (m_white.first == m_black.first) return true;
    // same column
    if (m_white.second == m_black.second) return true;
    // same diagonal
    return std::abs(m_white.first - m_black.first) ==
           std::abs(m_white.second - m_black.second);
}

chess_board::operator std::string() const {
    std::string board;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (r == m_white.first && c == m_white.second) {
                board += 'W';
            } else if (r == m_black.first && c == m_black.second) {
                board += 'B';
            } else {
                board += '_';
            }
            if (c < 7) board += ' ';
        }
        if (r < 7) board += '\n';
    }
    return board;
}

}  // namespace queen_attack
