#include "queen_attack.h"

#include <sstream>
#include <stdexcept>
#include <utility>

namespace queen_attack {

chess_board::chess_board(std::array<coordinate_t, 2U> white, std::array<coordinate_t, 2U> black)
{
    const bool white_valid{(white[0] < static_cast<coordinate_t>(8U)) && (white[1] < static_cast<coordinate_t>(8U))};
    const bool black_valid{(black[0] < static_cast<coordinate_t>(8U)) && (black[1] < static_cast<coordinate_t>(8U))};

    if(!(white_valid && black_valid))
    {
        throw std::domain_error("Queen position(s) out of board range");
    }

    if((white[0] == black[0]) && (white[1] == black[1]))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }

    m_white = white;
    m_black = black;
}

bool chess_board::can_attack() const noexcept
{
    const std::uint32_t white_row{static_cast<std::uint32_t>(m_white[0])};
    const std::uint32_t white_col{static_cast<std::uint32_t>(m_white[1])};
    const std::uint32_t black_row{static_cast<std::uint32_t>(m_black[0])};
    const std::uint32_t black_col{static_cast<std::uint32_t>(m_black[1])};

    const bool same_row{white_row == black_row};
    const bool same_col{white_col == black_col};
    const std::uint32_t row_diff{(white_row > black_row) ? (white_row - black_row) : (black_row - white_row)};
    const std::uint32_t col_diff{(white_col > black_col) ? (white_col - black_col) : (black_col - white_col)};
    const bool same_diag{row_diff == col_diff};

    return (same_row || same_col) || same_diag;
}

chess_board::operator std::string() const
{
    std::ostringstream board_builder{};

    for(std::uint32_t row{0U}; row < 8U; ++row)
    {
        for(std::uint32_t col{0U}; col < 8U; ++col)
        {
            char square{'_'};
            if((row == static_cast<std::uint32_t>(m_white[0])) && (col == static_cast<std::uint32_t>(m_white[1])))
            {
                square = 'W';
            }
            else if((row == static_cast<std::uint32_t>(m_black[0])) && (col == static_cast<std::uint32_t>(m_black[1])))
            {
                square = 'B';
            }
            board_builder << square;
            if(col < 7U)
            {
                board_builder << ' ';
            }
        }
        if(row < 7U)
        {
            board_builder << '\n';
        }
    }
    return board_builder.str();
}

std::pair<int, int> chess_board::white() const noexcept
{
    return {static_cast<int>(m_white[0]), static_cast<int>(m_white[1])};
}

std::pair<int, int> chess_board::black() const noexcept
{
    return {static_cast<int>(m_black[0]), static_cast<int>(m_black[1])};
}

}  // namespace queen_attack
