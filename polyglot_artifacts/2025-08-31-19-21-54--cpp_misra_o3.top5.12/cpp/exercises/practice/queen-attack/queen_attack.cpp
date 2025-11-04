#include "queen_attack.h"

#include <sstream>

namespace queen_attack {

chess_board::operator std::string() const
{
    std::ostringstream board_stream;

    for (board_dim_t row = 0; row < 8; ++row)
    {
        for (board_dim_t col = 0; col < 8; ++col)
        {
            char square_char = '_';

            if ((row == white_pos.first) && (col == white_pos.second))
            {
                square_char = 'W';
            }
            else if ((row == black_pos.first) && (col == black_pos.second))
            {
                square_char = 'B';
            }

            board_stream << square_char;

            if (col < 7)
            {
                board_stream << ' ';
            }
        }

        if (row < 7)
        {
            board_stream << '\n';
        }
    }

    return board_stream.str();
}

}  // namespace queen_attack
