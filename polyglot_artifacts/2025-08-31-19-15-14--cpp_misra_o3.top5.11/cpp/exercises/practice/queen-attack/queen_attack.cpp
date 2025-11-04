#include "queen_attack.h"

#include <array>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

using diff_t = std::int32_t;

chess_board::chess_board(coordinate white_pos, coordinate black_pos) : m_white(white_pos), m_black(black_pos)
{
    const auto in_range = [](index_t value) noexcept -> bool
    {
        return (value >= 0) && (value <= 7);
    };

    if(!(in_range(m_white.first) && in_range(m_white.second) &&
         in_range(m_black.first) && in_range(m_black.second)))
    {
        throw std::domain_error("Queen position out of range");
    }

    if((m_white == m_black))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::coordinate chess_board::white() const noexcept
{
    return m_white;
}

chess_board::coordinate chess_board::black() const noexcept
{
    return m_black;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row{m_white.first == m_black.first};
    const bool same_column{m_white.second == m_black.second};

    const diff_t row_diff{static_cast<diff_t>(m_white.first) - static_cast<diff_t>(m_black.first)};
    const diff_t col_diff{static_cast<diff_t>(m_white.second) - static_cast<diff_t>(m_black.second)};

    const bool same_diagonal{(std::abs(row_diff) == std::abs(col_diff))};

    return (same_row || same_column) || same_diagonal;
}

chess_board::operator std::string() const
{
    std::array<std::array<char, 8U>, 8U> board{};

    for(std::uint32_t r{0U}; r < 8U; ++r)
    {
        for(std::uint32_t c{0U}; c < 8U; ++c)
        {
            board[r][c] = '_';
        }
    }

    board[static_cast<std::size_t>(m_white.first)][static_cast<std::size_t>(m_white.second)] = 'W';
    board[static_cast<std::size_t>(m_black.first)][static_cast<std::size_t>(m_black.second)] = 'B';

    std::ostringstream oss;

    for(std::uint32_t r{0U}; r < 8U; ++r)
    {
        for(std::uint32_t c{0U}; c < 8U; ++c)
        {
            oss << board[r][c];

            if(c < 7U)
            {
                oss << ' ';
            }
        }

        if(r < 7U)
        {
            oss << '\n';
        }
    }

    return oss.str();
}

} // namespace queen_attack
