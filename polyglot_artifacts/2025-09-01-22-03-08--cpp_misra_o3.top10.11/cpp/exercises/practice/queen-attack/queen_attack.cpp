#include "queen_attack.h"

namespace queen_attack {

void chess_board::validate_position(std::pair<int, int> pos)
{
    if ((pos.first < 0) || (pos.first > 7) ||
        (pos.second < 0) || (pos.second > 7))
    {
        throw std::domain_error("position out of range");
    }
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : m_white{ static_cast<coord_t>(white.first), static_cast<coord_t>(white.second) },
      m_black{ static_cast<coord_t>(black.first), static_cast<coord_t>(black.second) }
{
    validate_position(white);
    validate_position(black);
    if ((white.first == black.first) && (white.second == black.second))
    {
        throw std::domain_error("queens cannot occupy the same square");
    }
}

std::pair<int, int> chess_board::white() const
{
    return { static_cast<int>(m_white.first), static_cast<int>(m_white.second) };
}

std::pair<int, int> chess_board::black() const
{
    return { static_cast<int>(m_black.first), static_cast<int>(m_black.second) };
}

bool chess_board::can_attack() const
{
    /* ensure no implicit integral promotion changes width or signedness */
    using wide_t = std::int16_t;

    const bool same_row = (m_white.first == m_black.first);
    const bool same_col = (m_white.second == m_black.second);

    const wide_t white_sum  = static_cast<wide_t>(m_white.first) + static_cast<wide_t>(m_white.second);
    const wide_t black_sum  = static_cast<wide_t>(m_black.first) + static_cast<wide_t>(m_black.second);
    const wide_t white_diff = static_cast<wide_t>(m_white.first) - static_cast<wide_t>(m_white.second);
    const wide_t black_diff = static_cast<wide_t>(m_black.first) - static_cast<wide_t>(m_black.second);

    const bool same_diag1 = (white_sum == black_sum);
    const bool same_diag2 = (white_diff == black_diff);

    return (same_row || same_col) || (same_diag1 || same_diag2);
}

}  // namespace queen_attack
