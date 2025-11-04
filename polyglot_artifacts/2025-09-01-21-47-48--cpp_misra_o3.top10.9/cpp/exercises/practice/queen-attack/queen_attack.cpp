#include "queen_attack.h"

#include <array>
#include <sstream>
#include <cstdint>
#include <stdexcept>
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(const Position& white, const Position& black)
    : white_{white}, black_{black}
{
    constexpr std::int32_t board_limit{8};

    if ((white_.first < 0) || (white_.second < 0) ||
        (black_.first < 0) || (black_.second < 0) ||
        (white_.first >= board_limit) || (white_.second >= board_limit) ||
        (black_.first >= board_limit) || (black_.second >= board_limit))
    {
        throw std::domain_error("Queen position out of range");
    }

    if (white_ == black_)
    {
        throw std::domain_error("Queens cannot share the same square");
    }
}

Position chess_board::white() const noexcept
{
    return white_;
}

Position chess_board::black() const noexcept
{
    return black_;
}

bool chess_board::can_attack() const noexcept
{
    const std::int32_t row_diff{white_.first - black_.first};
    const std::int32_t col_diff{white_.second - black_.second};

    const bool same_row{white_.first == black_.first};
    const bool same_col{white_.second == black_.second};
    const bool same_diagonal{std::abs(row_diff) == std::abs(col_diff)};

    return (same_row || same_col) || same_diagonal;
}

std::string chess_board::to_string() const
{
    constexpr std::int32_t board_limit{8};
    std::ostringstream oss{};

    for (std::int32_t row{0}; row < board_limit; ++row)
    {
        for (std::int32_t col{0}; col < board_limit; ++col)
        {
            char square{'O'};

            if ((row == white_.first) && (col == white_.second))
            {
                square = 'W';
            }
            else if ((row == black_.first) && (col == black_.second))
            {
                square = 'B';
            }

            oss << square;
            if (col < (board_limit - 1))
            {
                oss << ' ';
            }
        }
        if (row < (board_limit - 1))
        {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace queen_attack
