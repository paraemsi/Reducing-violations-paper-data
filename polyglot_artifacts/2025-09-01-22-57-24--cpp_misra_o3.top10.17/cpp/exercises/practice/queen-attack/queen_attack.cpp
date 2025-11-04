#include "queen_attack.h"

#include <sstream>
#include <stdexcept>

namespace queen_attack
{

namespace
{
    [[nodiscard]] bool is_valid_position(position_t pos) noexcept
    {
        return (pos.first < static_cast<coordinate_t>(8U))
            && (pos.second < static_cast<coordinate_t>(8U));
    }
} // anonymous namespace

chess_board::chess_board(position_t white_pos, position_t black_pos)
    : m_white{ white_pos }
    , m_black{ black_pos }
{
    if ((!is_valid_position(m_white)) || (!is_valid_position(m_black)))
    {
        throw std::domain_error("Queen position out of bounds");
    }

    if (m_white == m_black)
    {
        throw std::domain_error("Queens cannot occupy the same square");
    }
}

std::pair<std::int32_t, std::int32_t> chess_board::white() const
{
    return { static_cast<std::int32_t>(m_white.first),
             static_cast<std::int32_t>(m_white.second) };
}

std::pair<std::int32_t, std::int32_t> chess_board::black() const
{
    return { static_cast<std::int32_t>(m_black.first),
             static_cast<std::int32_t>(m_black.second) };
}

bool chess_board::can_attack() const
{
    /* same row */
    if (m_white.first == m_black.first)
    {
        return true;
    }

    /* same column */
    if (m_white.second == m_black.second)
    {
        return true;
    }

    /* same diagonal */
    auto row_diff = static_cast<coordinate_t>(
        (m_white.first > m_black.first)
            ? static_cast<std::uint16_t>(m_white.first) - static_cast<std::uint16_t>(m_black.first)
            : static_cast<std::uint16_t>(m_black.first) - static_cast<std::uint16_t>(m_white.first));

    auto col_diff = static_cast<coordinate_t>(
        (m_white.second > m_black.second)
            ? static_cast<std::uint16_t>(m_white.second) - static_cast<std::uint16_t>(m_black.second)
            : static_cast<std::uint16_t>(m_black.second) - static_cast<std::uint16_t>(m_white.second));

    return (row_diff == col_diff);
}

chess_board::operator std::string() const
{
    std::ostringstream oss;

    for (coordinate_t row = 0U; row < static_cast<coordinate_t>(8U); ++row)
    {
        for (coordinate_t col = 0U; col < static_cast<coordinate_t>(8U); ++col)
        {
            if ((row == m_white.first) && (col == m_white.second))
            {
                oss << 'W';
            }
            else if ((row == m_black.first) && (col == m_black.second))
            {
                oss << 'B';
            }
            else
            {
                oss << '_';
            }

            if (col < static_cast<coordinate_t>(7U))
            {
                oss << ' ';
            }
        }

        if (row < static_cast<coordinate_t>(7U))
        {
            oss << '\n';
        }
    }

    return oss.str();
}

} // namespace queen_attack
