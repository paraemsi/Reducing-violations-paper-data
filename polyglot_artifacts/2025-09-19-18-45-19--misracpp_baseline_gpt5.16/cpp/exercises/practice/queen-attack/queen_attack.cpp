#include "queen_attack.h"

#include <cmath>
#include <stdexcept>

namespace queen_attack {

namespace {
    inline bool is_valid(const position& p) {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    }
}

// chess_board member definitions
chess_board::chess_board(const position& white, const position& black)
    : m_white(white), m_black(black) {
    if (!is_valid(m_white) || !is_valid(m_black)) {
        throw std::domain_error("position out of bounds");
    }
    if (m_white == m_black) {
        throw std::domain_error("queens cannot occupy the same square");
    }
}

position chess_board::white() const {
    return m_white;
}

position chess_board::black() const {
    return m_black;
}

bool chess_board::can_attack() const {
    if (m_white.first == m_black.first || m_white.second == m_black.second) {
        return true;
    }
    return std::abs(m_white.first - m_black.first) == std::abs(m_white.second - m_black.second);
}

bool can_attack(const position& white, const position& black) {
    if (!is_valid(white) || !is_valid(black)) {
        throw std::domain_error("position out of bounds");
    }
    if (white == black) {
        throw std::domain_error("queens cannot occupy the same square");
    }

    // Same row or same column
    if (white.first == black.first || white.second == black.second) {
        return true;
    }

    // Same diagonal
    return std::abs(white.first - black.first) == std::abs(white.second - black.second);
}

}  // namespace queen_attack
