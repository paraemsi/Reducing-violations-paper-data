#include "queen_attack.h"

#include <cstdlib>     // std::abs
#include <stdexcept>
#include <sstream>

namespace queen_attack {

namespace {
constexpr std::int32_t board_min{0};
constexpr std::int32_t board_max{7};

static bool is_valid_coordinate(const chess_board::coordinate& pos)
{
    return ((pos.first >= board_min) && (pos.first <= board_max)
         && (pos.second >= board_min) && (pos.second <= board_max));
}
} // unnamed namespace

chess_board::chess_board() : m_white{0, 3}, m_black{7, 3}
{
}

chess_board::chess_board(coordinate white_pos, coordinate black_pos)
    : m_white{white_pos},
      m_black{black_pos}
{
    if ((white_pos == black_pos) || (!is_valid_coordinate(white_pos)) || (!is_valid_coordinate(black_pos))) {
        throw std::domain_error("invalid queen position");
    }
}

chess_board::coordinate chess_board::white() const
{
    return m_white;
}

chess_board::coordinate chess_board::black() const
{
    return m_black;
}

bool chess_board::can_attack() const
{
    if ((!is_valid_coordinate(m_white)) || (!is_valid_coordinate(m_black))) {
        return false;
    }

    const std::int32_t row_diff{m_white.first - m_black.first};
    const std::int32_t col_diff{m_white.second - m_black.second};

    return ((m_white.first == m_black.first)
         || (m_white.second == m_black.second)
         || (std::abs(row_diff) == std::abs(col_diff)));
}

chess_board::operator std::string() const
{
    std::ostringstream board_stream;

    for (std::int32_t row{board_min}; row <= board_max; ++row) {
        for (std::int32_t col{board_min}; col <= board_max; ++col) {
            char square{'_'};

            if ((row == m_white.first) && (col == m_white.second)) {
                square = 'W';
            } else if ((row == m_black.first) && (col == m_black.second)) {
                square = 'B';
            }

            board_stream << square;

            if (col < board_max) {
                board_stream << ' ';
            }
        }

        if (row < board_max) {
            board_stream << '\n';
        }
    }

    return board_stream.str();
}

}  // namespace queen_attack
