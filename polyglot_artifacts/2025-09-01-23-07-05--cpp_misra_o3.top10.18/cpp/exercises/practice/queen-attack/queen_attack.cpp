#include "queen_attack.h"

#include <stdexcept>
#include <sstream>

namespace queen_attack {

namespace
{
    constexpr std::int32_t board_size { 8 };

    using position = std::pair<std::int32_t, std::int32_t>;

    [[nodiscard]] bool is_diagonal(position pos_a, position pos_b) noexcept
    {
        const std::int32_t row_diff { (pos_a.first > pos_b.first) ? (pos_a.first - pos_b.first)
                                                                  : (pos_b.first - pos_a.first) };
        const std::int32_t col_diff { (pos_a.second > pos_b.second) ? (pos_a.second - pos_b.second)
                                                                    : (pos_b.second - pos_a.second) };
        return (row_diff == col_diff);
    }
} // anonymous namespace

chess_board::chess_board(position white_pos, position black_pos)
    : m_white { white_pos }, m_black { black_pos }
{
    if((white_pos == black_pos) ||
       (!are_positions_valid(white_pos)) ||
       (!are_positions_valid(black_pos)))
    {
        throw std::domain_error("Invalid board positions");
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
    if((m_white.first == chess_board::invalid_coord) || (m_black.first == chess_board::invalid_coord))
    {
        return false;
    }

    if(m_white.first == m_black.first)
    {
        return true;
    }

    if(m_white.second == m_black.second)
    {
        return true;
    }

    if(is_diagonal(m_white, m_black))
    {
        return true;
    }

    return false;
}

bool chess_board::are_positions_valid(position pos) noexcept
{
    return ((pos.first >= 0) && (pos.first < board_size) &&
            (pos.second >= 0) && (pos.second < board_size));
}

std::string chess_board::to_string() const
{
    std::ostringstream oss {};

    for(std::int32_t row { 0 }; row < board_size; ++row)
    {
        for(std::int32_t col { 0 }; col < board_size; ++col)
        {
            if((row == m_white.first) && (col == m_white.second))
            {
                oss << 'W';
            }
            else if((row == m_black.first) && (col == m_black.second))
            {
                oss << 'B';
            }
            else
            {
                oss << '_';
            }

            if(col < (board_size - 1))
            {
                oss << ' ';
            }
        }

        if(row < (board_size - 1))
        {
            oss << '\n';
        }
    }

    return oss.str();
}

chess_board::operator std::string() const
{
    return to_string();
}

}  // namespace queen_attack
