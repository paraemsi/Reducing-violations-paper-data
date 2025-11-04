#include "queen_attack.h"
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board() noexcept
    : m_white(position_t { static_cast<coordinate_t>(0U),
                           static_cast<coordinate_t>(3U) }),
      m_black(position_t { static_cast<coordinate_t>(7U),
                           static_cast<coordinate_t>(3U) })
{
    /* default starting positions */
}

chess_board::chess_board(std::pair<int, int> white_pos,
                         std::pair<int, int> black_pos)
    : m_white(position_t { static_cast<coordinate_t>(white_pos.first),
                           static_cast<coordinate_t>(white_pos.second) }),
      m_black(position_t { static_cast<coordinate_t>(black_pos.first),
                           static_cast<coordinate_t>(black_pos.second) })
{
    if (!is_valid(m_white) || !is_valid(m_black)) {
        throw std::domain_error("Queen position out of range (0..7)");
    }
    if ((m_white.first == m_black.first) && (m_white.second == m_black.second)) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

std::pair<int, int> chess_board::white() const noexcept
{
    return std::pair<int, int> { static_cast<int>(m_white.first),
                                 static_cast<int>(m_white.second) };
}

std::pair<int, int> chess_board::black() const noexcept
{
    return std::pair<int, int> { static_cast<int>(m_black.first),
                                 static_cast<int>(m_black.second) };
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row = (m_white.first == m_black.first);
    const bool same_col = (m_white.second == m_black.second);

    const std::uint16_t row_w =
        static_cast<std::uint16_t>(m_white.first);
    const std::uint16_t row_b =
        static_cast<std::uint16_t>(m_black.first);
    const std::uint16_t col_w =
        static_cast<std::uint16_t>(m_white.second);
    const std::uint16_t col_b =
        static_cast<std::uint16_t>(m_black.second);

    const std::uint16_t row_diff =
        (row_w > row_b) ? (row_w - row_b) : (row_b - row_w);
    const std::uint16_t col_diff =
        (col_w > col_b) ? (col_w - col_b) : (col_b - col_w);

    const bool same_diag = (row_diff == col_diff);

    return (same_row || same_col || same_diag);
}

bool chess_board::is_valid(position_t pos) noexcept
{
    return (pos.first < static_cast<coordinate_t>(8U)) &&
           (pos.second < static_cast<coordinate_t>(8U));
}

}  // namespace queen_attack
