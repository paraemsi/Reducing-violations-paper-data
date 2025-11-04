#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(std::pair<board_index_t, board_index_t> white, std::pair<board_index_t, board_index_t> black)
    : white_pos(white), black_pos(black)
{
    // Validate positions are on the board
    if ((white.first > 7U) ||
        (white.second > 7U) ||
        (black.first > 7U) ||
        (black.second > 7U)) {
        throw std::domain_error("Position out of bounds");
    }
    // Validate positions are not the same
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
    board_index_t white_row = white_pos.first;
    board_index_t white_col = white_pos.second;
    board_index_t black_row = black_pos.first;
    board_index_t black_col = black_pos.second;

    // Same row
    if (white_row == black_row) {
        return true;
    }
    // Same column
    if (white_col == black_col) {
        return true;
    }
    // Same diagonal
    if ((static_cast<int>(white_row) - static_cast<int>(black_row)) == (static_cast<int>(white_col) - static_cast<int>(black_col))) {
        return true;
    }
    if ((static_cast<int>(white_row) - static_cast<int>(black_row)) == (static_cast<int>(black_col) - static_cast<int>(white_col))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
