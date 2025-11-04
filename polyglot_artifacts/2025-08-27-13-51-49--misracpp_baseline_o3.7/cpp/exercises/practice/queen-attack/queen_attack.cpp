#include "queen_attack.h"

#include <stdexcept>
#include <sstream>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white,
                         std::pair<int, int> black)
    : m_white{white}, m_black{black}
{
    if (!is_valid_position(m_white) || !is_valid_position(m_black)) {
        throw std::domain_error{"Queen position must be on the board"};
    }
    if (m_white == m_black) {
        throw std::domain_error{"Queens cannot occupy the same position"};
    }
}

std::pair<int, int> chess_board::white() const
{
    return m_white;
}

std::pair<int, int> chess_board::black() const
{
    return m_black;
}

bool chess_board::can_attack() const
{
    // same row or same column
    if (m_white.first == m_black.first || m_white.second == m_black.second) {
        return true;
    }
    // diagonal : |Δrow| == |Δcol|
    return std::abs(m_white.first - m_black.first) ==
           std::abs(m_white.second - m_black.second);
}

chess_board::operator std::string() const
{
    std::ostringstream out;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (row == m_white.first && col == m_white.second) {
                out << 'W';
            } else if (row == m_black.first && col == m_black.second) {
                out << 'B';
            } else {
                out << '_';
            }
            if (col != 7) {
                out << ' ';
            }
        }
        if (row != 7) {
            out << '\n';
        }
    }
    return out.str();
}

bool chess_board::is_valid_position(const std::pair<int, int>& pos)
{
    return pos.first >= 0 && pos.first < 8 &&
           pos.second >= 0 && pos.second < 8;
}

}  // namespace queen_attack
