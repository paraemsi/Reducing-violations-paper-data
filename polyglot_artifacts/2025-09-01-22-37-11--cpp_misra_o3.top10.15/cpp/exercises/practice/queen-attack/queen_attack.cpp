#include "queen_attack.h"

#include <stdexcept>
#include <cstdlib>

namespace queen_attack {

namespace {

[[nodiscard]] bool same_row(const std::pair<coordinate_t, coordinate_t>& a,
                            const std::pair<coordinate_t, coordinate_t>& b) noexcept {
    return (a.first == b.first);
}

[[nodiscard]] bool same_col(const std::pair<coordinate_t, coordinate_t>& a,
                            const std::pair<coordinate_t, coordinate_t>& b) noexcept {
    return (a.second == b.second);
}

[[nodiscard]] bool same_diag(const std::pair<coordinate_t, coordinate_t>& a,
                             const std::pair<coordinate_t, coordinate_t>& b) noexcept {
    const std::int16_t row_diff =
        static_cast<std::int16_t>(a.first) - static_cast<std::int16_t>(b.first);
    const std::int16_t col_diff =
        static_cast<std::int16_t>(a.second) - static_cast<std::int16_t>(b.second);
    return (std::abs(row_diff) == std::abs(col_diff));
}

}  // unnamed namespace

bool chess_board::is_valid_position(const std::pair<coordinate_t, coordinate_t>& pos) const noexcept {
    return ((pos.first < board_size) && (pos.second < board_size));
}

chess_board::chess_board(std::pair<coordinate_t, coordinate_t> white,
                         std::pair<coordinate_t, coordinate_t> black)
    : m_white{white}, m_black{black} {
    if (!is_valid_position(m_white) || !is_valid_position(m_black)) {
        throw std::domain_error("Queen position out of bounds");
    }
    if ((m_white.first == m_black.first) && (m_white.second == m_black.second)) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

bool chess_board::can_attack() const noexcept {
    return (same_row(m_white, m_black) ||
            same_col(m_white, m_black) ||
            same_diag(m_white, m_black));
}

chess_board::operator std::string() const {
    std::string out;
    for (coordinate_t row = static_cast<coordinate_t>(0U); row < board_size; ++row) {
        for (coordinate_t col = static_cast<coordinate_t>(0U); col < board_size; ++col) {
            if ((row == m_white.first) && (col == m_white.second)) {
                out += 'W';
            } else if ((row == m_black.first) && (col == m_black.second)) {
                out += 'B';
            } else {
                out += '_';
            }
            if (col < (board_size - static_cast<coordinate_t>(1U))) {
                out += ' ';
            }
        }
        if (row < (board_size - static_cast<coordinate_t>(1U))) {
            out += '\n';
        }
    }
    return out;
}

std::pair<coordinate_t, coordinate_t> chess_board::white() const noexcept {
    return m_white;
}

std::pair<coordinate_t, coordinate_t> chess_board::black() const noexcept {
    return m_black;
}

}  // namespace queen_attack
