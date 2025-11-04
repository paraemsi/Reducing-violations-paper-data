#include "queen_attack.h"

#include <stdexcept>
#include <cstdint>
#include <string>

namespace queen_attack {

using diff_t = std::int16_t;

namespace {

[[nodiscard]] constexpr diff_t abs_val(diff_t value) noexcept
{
    return (value < static_cast<diff_t>(0)) ? static_cast<diff_t>(-value) : value;
}

/* Validate that a queen position lies within the bounds of an 8 × 8 board. */
[[nodiscard]] bool is_valid_position(const std::pair<coordinate_t, coordinate_t>& pos) noexcept
{
    return ((pos.first < static_cast<coordinate_t>(8U)) &&
            (pos.second < static_cast<coordinate_t>(8U)));
}

} // unnamed namespace

chess_board::chess_board(const std::pair<coordinate_t, coordinate_t> white,
                         const std::pair<coordinate_t, coordinate_t> black)
    : m_white(white),
      m_black(black)
{
    if ((!is_valid_position(m_white)) || (!is_valid_position(m_black))) {
        throw std::domain_error("Queen position out of range");
    }
    if (m_white == m_black) {
        throw std::domain_error("Queens cannot share the same position");
    }
}

bool chess_board::can_attack() const
{
    const bool same_row = (m_white.first == m_black.first);
    const bool same_col = (m_white.second == m_black.second);

    const diff_t row_diff = static_cast<diff_t>(static_cast<diff_t>(m_white.first) -
                                                static_cast<diff_t>(m_black.first));
    const diff_t col_diff = static_cast<diff_t>(static_cast<diff_t>(m_white.second) -
                                                static_cast<diff_t>(m_black.second));

    const bool same_diag = (abs_val(row_diff) == abs_val(col_diff));

    return (same_row || same_col || same_diag);
}

chess_board::operator std::string() const
{
    std::string board;
    for (coordinate_t row = 0U; row < static_cast<coordinate_t>(8U); ++row) {
        for (coordinate_t col = 0U; col < static_cast<coordinate_t>(8U); ++col) {
            char square = '_';
            if ((m_white.first == row) && (m_white.second == col)) {
                square = 'W';
            } else if ((m_black.first == row) && (m_black.second == col)) {
                square = 'B';
            } else {
                /* square remains '_' */
            }

            board += square;
            if (col < static_cast<coordinate_t>(7U)) {
                board += ' ';
            }
        }
        if (row < static_cast<coordinate_t>(7U)) {
            board += '\n';
        }
    }
    return board;
}

std::pair<coordinate_t, coordinate_t> chess_board::white() const noexcept
{
    return m_white;
}

std::pair<coordinate_t, coordinate_t> chess_board::black() const noexcept
{
    return m_black;
}

}  // namespace queen_attack
