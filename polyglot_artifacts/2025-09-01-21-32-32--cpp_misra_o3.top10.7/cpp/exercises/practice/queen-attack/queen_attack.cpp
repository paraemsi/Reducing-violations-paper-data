#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(coordinate_t white_pos, coordinate_t black_pos)
{
    validate_position(white_pos);
    validate_position(black_pos);

    m_white = storage_coordinate_t(static_cast<std::uint8_t>(white_pos.first),
                                   static_cast<std::uint8_t>(white_pos.second));
    m_black = storage_coordinate_t(static_cast<std::uint8_t>(black_pos.first),
                                   static_cast<std::uint8_t>(black_pos.second));

    if ((m_white == m_black)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

coordinate_t chess_board::white() const noexcept
{
    return coordinate_t(static_cast<coordinate_value_t>(m_white.first),
                        static_cast<coordinate_value_t>(m_white.second));
}

coordinate_t chess_board::black() const noexcept
{
    return coordinate_t(static_cast<coordinate_value_t>(m_black.first),
                        static_cast<coordinate_value_t>(m_black.second));
}

bool chess_board::can_attack() const noexcept
{
    return can_attack(m_white, m_black);
}

chess_board::operator std::string() const
{
    std::string board_str {};
    for (std::uint8_t row = static_cast<std::uint8_t>(0U);
         row < static_cast<std::uint8_t>(8U);
         ++row) {
        for (std::uint8_t col = static_cast<std::uint8_t>(0U);
             col < static_cast<std::uint8_t>(8U);
             ++col) {
            if ((row == m_white.first) && (col == m_white.second)) {
                board_str += 'W';
            } else if ((row == m_black.first) && (col == m_black.second)) {
                board_str += 'B';
            } else {
                board_str += '_';
            }

            if (col < static_cast<std::uint8_t>(7U)) {
                board_str += ' ';
            }
        }

        if (row < static_cast<std::uint8_t>(7U)) {
            board_str += '\n';
        }
    }
    return board_str;
}

bool chess_board::can_attack(const storage_coordinate_t& white_pos,
                             const storage_coordinate_t& black_pos) noexcept
{
    if (white_pos.first == black_pos.first) {
        return true; // same row
    }

    if (white_pos.second == black_pos.second) {
        return true; // same column
    }

    const std::uint16_t row_diff =
        (white_pos.first > black_pos.first)
            ? static_cast<std::uint16_t>(white_pos.first - black_pos.first)
            : static_cast<std::uint16_t>(black_pos.first - white_pos.first);

    const std::uint16_t col_diff =
        (white_pos.second > black_pos.second)
            ? static_cast<std::uint16_t>(white_pos.second - black_pos.second)
            : static_cast<std::uint16_t>(black_pos.second - white_pos.second);

    return row_diff == col_diff; // same diagonal
}

void chess_board::validate_position(const coordinate_t& position)
{
    if ((position.first < static_cast<coordinate_value_t>(0)) ||
        (position.first > static_cast<coordinate_value_t>(7)) ||
        (position.second < static_cast<coordinate_value_t>(0)) ||
        (position.second > static_cast<coordinate_value_t>(7))) {
        throw std::domain_error("Position is outside the board");
    }
}

}  // namespace queen_attack
