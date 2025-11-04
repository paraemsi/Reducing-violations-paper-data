#include "queen_attack.h"

#include <stdexcept>
#include <string>

namespace queen_attack {

void chess_board::validate(position pos)
{
    if (!((pos.row < board_size) && (pos.column < board_size))) {
        throw std::domain_error("Position out of bounds");
    }
}

chess_board::chess_board(position white, position black)
    : white_{white}, black_{black}
{
    validate(white_);
    validate(black_);
    if ((white_.row == black_.row) && (white_.column == black_.column)) {
        throw std::domain_error("Queens cannot share the same position");
    }
}

position chess_board::white() const
{
    return white_;
}

position chess_board::black() const
{
    return black_;
}

bool chess_board::can_attack() const
{
    if (white_.row == black_.row) {
        return true;
    }
    if (white_.column == black_.column) {
        return true;
    }

    using diff_t = std::uint16_t;

    const diff_t w_row = static_cast<diff_t>(white_.row);
    const diff_t b_row = static_cast<diff_t>(black_.row);
    const diff_t w_col = static_cast<diff_t>(white_.column);
    const diff_t b_col = static_cast<diff_t>(black_.column);

    const diff_t drow = (w_row >= b_row)
                            ? static_cast<diff_t>(w_row - b_row)
                            : static_cast<diff_t>(b_row - w_row);

    const diff_t dcol = (w_col >= b_col)
                            ? static_cast<diff_t>(w_col - b_col)
                            : static_cast<diff_t>(b_col - w_col);

    if (drow == dcol) {
        return true;
    }

    return false;
}

chess_board::operator std::string() const
{
    std::string out;
    const position::value_type last = static_cast<position::value_type>(7U);

    for (position::value_type r = static_cast<position::value_type>(0U); r < board_size; ++r) {
        for (position::value_type c = static_cast<position::value_type>(0U); c < board_size; ++c) {
            char ch = '_';
            if ((r == white_.row) && (c == white_.column)) {
                ch = 'W';
            } else {
                if ((r == black_.row) && (c == black_.column)) {
                    ch = 'B';
                } else {
                    ch = '_';
                }
            }
            out.push_back(ch);
            if (c != last) {
                out.push_back(' ');
            }
        }
        if (r != last) {
            out.push_back('\n');
        }
    }

    return out;
}

}  // namespace queen_attack
