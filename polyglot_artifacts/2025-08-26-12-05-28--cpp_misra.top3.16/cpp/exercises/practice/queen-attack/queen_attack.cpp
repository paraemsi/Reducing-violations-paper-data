#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(std::pair<board_index_t, board_index_t> white, std::pair<board_index_t, board_index_t> black)
    : white_pos(white), black_pos(black)
{
    // Check for out-of-bounds
    if ((white.first > 7U) || (white.second > 7U) ||
        (black.first > 7U) || (black.second > 7U)) {
        throw std::domain_error("Position out of bounds");
    }
    // Check for same position
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<board_index_t, board_index_t> chess_board::white(void) const
{
    return white_pos;
}

std::pair<board_index_t, board_index_t> chess_board::black(void) const
{
    return black_pos;
}

bool chess_board::can_attack(void) const
{
    board_index_t w_row = white_pos.first;
    board_index_t w_col = white_pos.second;
    board_index_t b_row = black_pos.first;
    board_index_t b_col = black_pos.second;

    // Same row
    if (w_row == b_row) {
        return true;
    }
    // Same column
    if (w_col == b_col) {
        return true;
    }
    // Same diagonal
    if ((w_row > b_row) ? ((w_row - b_row) == (w_col > b_col ? (w_col - b_col) : (b_col - w_col)))
                       : ((b_row - w_row) == (w_col > b_col ? (w_col - b_col) : (b_col - w_col)))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
