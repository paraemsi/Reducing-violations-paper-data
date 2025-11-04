#include "queen_attack.h"

#include <sstream>
#include <stdexcept>

namespace queen_attack {

namespace {

/* Helper to check a coordinate is within the board. */
inline bool is_within_board(std::uint8_t value) noexcept
{
    return (value < chess_board::board_size);
}

} // unnamed namespace

/* static */ void chess_board::validate_position(const position& pos)
{
    if ((!is_within_board(pos.row)) || (!is_within_board(pos.column))) {
        throw std::domain_error("Position out of bounds");
    }
}

chess_board::chess_board() noexcept
    : m_white{0U, 3U}, m_black{7U, 3U}
{
    /* default starting positions already valid */
}

chess_board::chess_board(const position& white_pos, const position& black_pos)
    : m_white{white_pos}, m_black{black_pos}
{
    validate_position(m_white);
    validate_position(m_black);

    if (m_white == m_black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::position chess_board::white() const noexcept
{
    return m_white;
}

chess_board::position chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    /* same row */
    if (m_white.row == m_black.row) {
        return true;
    }

    /* same column */
    if (m_white.column == m_black.column) {
        return true;
    }

    /* same diagonal : absolute row diff == absolute col diff */
    const std::uint8_t row_diff{
        static_cast<std::uint8_t>(
            (m_white.row > m_black.row) ? (m_white.row - m_black.row)
                                        : (m_black.row - m_white.row))};

    const std::uint8_t col_diff{
        static_cast<std::uint8_t>(
            (m_white.column > m_black.column) ? (m_white.column - m_black.column)
                                              : (m_black.column - m_white.column))};

    return (row_diff == col_diff);
}

std::string chess_board::board() const
{
    std::ostringstream oss{};

    for (std::uint8_t row{0U}; row < board_size; ++row) {
        for (std::uint8_t col{0U}; col < board_size; ++col) {
            char cell{'_'};

            if ((row == m_white.row) && (col == m_white.column)) {
                cell = 'W';
            } else if ((row == m_black.row) && (col == m_black.column)) {
                cell = 'B';
            }

            oss << cell;

            if (col < (board_size - 1U)) {
                oss << ' ';
            }
        }

        if (row < (board_size - 1U)) {
            oss << '\n';
        }
    }

    return oss.str();
}

chess_board::chess_board(const std::pair<int, int>& white_pos,
                         const std::pair<int, int>& black_pos)
    : chess_board{position(white_pos), position(black_pos)}
{
}

}  // namespace queen_attack
