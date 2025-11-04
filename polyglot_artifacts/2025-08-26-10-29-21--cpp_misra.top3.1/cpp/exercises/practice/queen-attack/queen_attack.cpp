#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_pos(static_cast<board_index_t>(white.first), static_cast<board_index_t>(white.second)),
      black_pos(static_cast<board_index_t>(black.first), static_cast<board_index_t>(black.second))
{
    // Validate board positions are in range [0, 7]
    if ((white.first < 0) || (white.first > 7) ||
        (white.second < 0) || (white.second > 7) ||
        (black.first < 0) || (black.first > 7) ||
        (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Position out of range");
    }
    // Validate that the two positions are not the same
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const
{
    return std::make_pair(static_cast<int>(white_pos.first), static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const
{
    return std::make_pair(static_cast<int>(black_pos.first), static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const
{
    // Row, column, or diagonal
    const board_index_t w_row = white_pos.first;
    const board_index_t w_col = white_pos.second;
    const board_index_t b_row = black_pos.first;
    const board_index_t b_col = black_pos.second;

    // Same row
    if(w_row == b_row) {
        return true;
    }
    // Same column
    if(w_col == b_col) {
        return true;
    }
    // Same diagonal
    if(((w_row > b_row) ? (w_row - b_row) : (b_row - w_row)) == ((w_col > b_col) ? (w_col - b_col) : (b_col - w_col))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
