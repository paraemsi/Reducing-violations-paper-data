#include "queen_attack.h"
#include <stdexcept>

namespace queen_attack {

bool chess_board::positions_equal(position_t lhs, position_t rhs) noexcept
{
    return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
}

bool chess_board::on_same_row(position_t lhs, position_t rhs) noexcept
{
    return (lhs.first == rhs.first);
}

bool chess_board::on_same_column(position_t lhs, position_t rhs) noexcept
{
    return (lhs.second == rhs.second);
}

bool chess_board::on_same_diagonal(position_t lhs, position_t rhs) noexcept
{
    const std::int8_t row_diff =
        static_cast<std::int8_t>(lhs.first) - static_cast<std::int8_t>(rhs.first);
    const std::int8_t col_diff =
        static_cast<std::int8_t>(lhs.second) - static_cast<std::int8_t>(rhs.second);

    return ((row_diff == col_diff) ||
            (row_diff == static_cast<std::int8_t>(-col_diff)));
}

chess_board::chess_board(position_t white, position_t black) :
    m_white{white},
    m_black{black}
{
    if ((white.first >= board_size) || (white.second >= board_size) ||
        (black.first >= board_size) || (black.second >= board_size))
    {
        throw std::domain_error("queen position out of bounds");
    }

    if (positions_equal(white, black))
    {
        throw std::domain_error("queens cannot occupy the same position");
    }
}

bool chess_board::can_attack() const noexcept
{
    if (on_same_row(m_white, m_black))
    {
        return true;
    }
    if (on_same_column(m_white, m_black))
    {
        return true;
    }
    if (on_same_diagonal(m_white, m_black))
    {
        return true;
    }
    return false;
}

std::pair<int, int> chess_board::white() const noexcept
{
    /*  Explicit cast from std::uint8_t to int is intentional and safe
        because board coordinates are limited to 0–7. */
    return {static_cast<int>(m_white.first),
            static_cast<int>(m_white.second)};
}

std::pair<int, int> chess_board::black() const noexcept
{
    return {static_cast<int>(m_black.first),
            static_cast<int>(m_black.second)};
}

chess_board::operator std::string() const
{
    std::string result{};
    for (std::uint8_t r = 0U; r < board_size; ++r)
    {
        for (std::uint8_t c = 0U; c < board_size; ++c)
        {
            char symbol{'_'};
            if ((r == m_white.first) && (c == m_white.second))
            {
                symbol = 'W';
            }
            else
            {
                if ((r == m_black.first) && (c == m_black.second))
                {
                    symbol = 'B';
                }
            }

            result.push_back(symbol);
            if (c < (board_size - 1U))
            {
                result.push_back(' ');
            }
        }
        result.push_back('\n');
    }
    return result;
}

} // namespace queen_attack
