#include "queen_attack.h"
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : m_white{white}, m_black{black} {

    auto in_bounds = [](const std::pair<int, int>& pos) {
        return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
    };

    if (!in_bounds(white) || !in_bounds(black)) {
        throw std::domain_error{"Queen position out of board range"};
    }
    if (white == black) {
        throw std::domain_error{"Queens cannot share the same square"};
    }
}

std::pair<int, int> chess_board::white() const {
    return m_white;
}

std::pair<int, int> chess_board::black() const {
    return m_black;
}

bool chess_board::can_attack() const {
    // same row
    if (m_white.first == m_black.first) {
        return true;
    }
    // same column
    if (m_white.second == m_black.second) {
        return true;
    }
    // same diagonal
    return std::abs(m_white.first - m_black.first) ==
           std::abs(m_white.second - m_black.second);
}

}  // namespace queen_attack
