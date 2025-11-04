#include "queen_attack.h"

#include <sstream>
#include <cstdint>

namespace queen_attack {

void chess_board::validate_position(const position_t pos)
{
    if((pos.first >= board_size) || (pos.second >= board_size))
    {
        throw std::domain_error("Position out of bounds");
    }
}

chess_board::chess_board(const position_t white_in, const position_t black_in)
    : white_{white_in},
      black_{black_in}
{
    validate_position(white_in);
    validate_position(black_in);

    if((white_in.first == black_in.first) && (white_in.second == black_in.second))
    {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position_t chess_board::white() const noexcept
{
    return white_;
}

position_t chess_board::black() const noexcept
{
    return black_;
}

bool chess_board::can_attack() const noexcept
{
    const bool same_row    = (white_.first == black_.first);
    const bool same_column = (white_.second == black_.second);

    const coordinate_t row_diff =
        (white_.first > black_.first) ? (white_.first - black_.first)
                                      : (black_.first - white_.first);

    const coordinate_t col_diff =
        (white_.second > black_.second) ? (white_.second - black_.second)
                                        : (black_.second - white_.second);

    const bool same_diagonal = (row_diff == col_diff);

    return (same_row || same_column || same_diagonal);
}

chess_board::operator std::string() const
{
    std::ostringstream oss;

    const coordinate_t board_limit = board_size;

    for(coordinate_t row = static_cast<coordinate_t>(0); row < board_limit; ++row)
    {
        for(coordinate_t col = static_cast<coordinate_t>(0); col < board_limit; ++col)
        {
            char square = '_';

            if((row == white_.first) &&
               (col == white_.second))
            {
                square = 'W';
            }
            else if((row == black_.first) &&
                    (col == black_.second))
            {
                square = 'B';
            }

            oss << square;

            if(col < (board_limit - static_cast<coordinate_t>(1)))
            {
                oss << ' ';
            }
        }

        if(row < (board_limit - static_cast<coordinate_t>(1)))
        {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace queen_attack
