#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(std::pair<board_index_t, board_index_t> white, std::pair<board_index_t, board_index_t> black)
    : white_pos(white), black_pos(black)
{
    // Validate positions are on the board
    if ((white.first > 7) ||
        (white.second > 7) ||
        (black.first > 7) ||
        (black.second > 7)) {
        throw std::domain_error("Queen position out of bounds");
    }
    // Validate positions are not the same
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<board_index_t, board_index_t> chess_board::white() const
{
    return white_pos;
}

std::pair<board_index_t, board_index_t> chess_board::black() const
{
    return black_pos;
}

bool chess_board::can_attack() const
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
    if (((w_row > b_row) ? (w_row - b_row) : (b_row - w_row)) ==
        ((w_col > b_col) ? (w_col - b_col) : (b_col - w_col))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
