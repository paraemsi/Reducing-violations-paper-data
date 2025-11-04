#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(const std::pair<board_index_t, board_index_t>& white_pos,
                         const std::pair<board_index_t, board_index_t>& black_pos)
    : white_position(white_pos), black_position(black_pos)
{
}

std::pair<int, int> chess_board::to_int_pair(const std::pair<board_index_t, board_index_t>& pos) noexcept
{
    return std::make_pair(static_cast<int>(pos.first), static_cast<int>(pos.second));
}

std::pair<int, int> chess_board::white() const
{
    return to_int_pair(white_position);
}

std::pair<int, int> chess_board::black() const
{
    return to_int_pair(black_position);
}

bool chess_board::can_attack() const
{
    // Row, column, or diagonal
    board_index_t white_row = white_position.first;
    board_index_t white_col = white_position.second;
    board_index_t black_row = black_position.first;
    board_index_t black_col = black_position.second;

    // Same row
    if (white_row == black_row) {
        return true;
    }
    // Same column
    if (white_col == black_col) {
        return true;
    }
    // Same diagonal
    if ((white_row > black_row) ? ((white_row - black_row) == (white_col > black_col ? (white_col - black_col) : (black_col - white_col)))
                               : ((black_row - white_row) == (white_col > black_col ? (white_col - black_col) : (black_col - white_col)))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
