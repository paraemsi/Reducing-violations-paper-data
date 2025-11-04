#include "queen_attack.h"

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos(white), black_pos(black)
{
    // Validate positions are on the board
    if ((white.first < 0) || (white.first > 7) || (white.second < 0) || (white.second > 7) ||
        (black.first < 0) || (black.first > 7) || (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Queen position out of bounds");
    }
    // Validate positions are not the same
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const
{
    return white_pos;
}

std::pair<int, int> chess_board::black() const
{
    return black_pos;
}

bool chess_board::can_attack() const
{
    int white_row = white_pos.first;
    int white_col = white_pos.second;
    int black_row = black_pos.first;
    int black_col = black_pos.second;

    // Same row
    if (white_row == black_row) {
        return true;
    }
    // Same column
    if (white_col == black_col) {
        return true;
    }
    // Same diagonal
    if (((white_row - black_row) == (white_col - black_col)) ||
        ((white_row - black_row) == (black_col - white_col))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
