#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(board_index_t white_row, board_index_t white_col, board_index_t black_row, board_index_t black_col)
    : white_pos(white_row, white_col), black_pos(black_row, black_col)
{
    if ((white_row > 7U) || (white_col > 7U) || (black_row > 7U) || (black_col > 7U)) {
        throw std::domain_error("Queen position out of bounds");
    }
    if ((white_row == black_row) && (white_col == black_col)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos(static_cast<board_index_t>(white.first), static_cast<board_index_t>(white.second)),
      black_pos(static_cast<board_index_t>(black.first), static_cast<board_index_t>(black.second))
{
    if ((white.first < 0) || (white.first > 7) || (white.second < 0) || (white.second > 7) ||
        (black.first < 0) || (black.first > 7) || (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Queen position out of bounds");
    }
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
    // Queens can attack if they are on the same row, column, or diagonal
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
    if ((white_row > black_row) ? ((white_row - black_row) == (white_col > black_col ? (white_col - black_col) : (black_col - white_col)))
                               : ((black_row - white_row) == (white_col > black_col ? (white_col - black_col) : (black_col - white_col)))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
