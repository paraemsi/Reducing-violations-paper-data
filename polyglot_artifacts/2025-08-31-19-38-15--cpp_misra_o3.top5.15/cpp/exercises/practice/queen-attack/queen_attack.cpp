#include "queen_attack.h"
#include <sstream>
#include <stdexcept>

namespace queen_attack {

bool chess_board::is_valid(const position_t& position)
{
    return ((position.first < 8) && (position.second < 8));
}

chess_board::chess_board(position_t white_position, position_t black_position)
    : white_pos_{white_position}, black_pos_{black_position}
{
    if ((white_position == black_position) ||
        (!is_valid(white_position))      ||
        (!is_valid(black_position)))
    {
        throw std::domain_error("Invalid queen position");
    }
}

position_t chess_board::white() const
{
    return white_pos_;
}

position_t chess_board::black() const
{
    return black_pos_;
}

bool chess_board::can_attack() const
{
    const bool same_row    = (white_pos_.first  == black_pos_.first);
    const bool same_column = (white_pos_.second == black_pos_.second);

    /*  Compute absolute row / column differences using the signed
        coordinate_t type to keep category, size and signed-ness identical,
        as required by the MISRA-C++ numerical conversion rule. */
    const coordinate_t row_diff =
        (white_pos_.first > black_pos_.first) ?
        (white_pos_.first  - black_pos_.first) :
        (black_pos_.first  - white_pos_.first);

    const coordinate_t col_diff =
        (white_pos_.second > black_pos_.second) ?
        (white_pos_.second - black_pos_.second) :
        (black_pos_.second - white_pos_.second);

    const bool same_diagonal = (row_diff == col_diff);

    return (same_row || same_column || same_diagonal);
}

chess_board::operator std::string() const
{
    std::ostringstream oss;

    for (coordinate_t row = 0; row < 8; ++row)
    {
        for (coordinate_t col = 0; col < 8; ++col)
        {
            char cell_char = '_';

            if ((row == white_pos_.first) && (col == white_pos_.second))
            {
                cell_char = 'W';
            }
            else if ((row == black_pos_.first) && (col == black_pos_.second))
            {
                cell_char = 'B';
            }

            oss << cell_char;
            if (col < 7)
            {
                oss << ' ';
            }
        }

        if (row < 7)
        {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace queen_attack
