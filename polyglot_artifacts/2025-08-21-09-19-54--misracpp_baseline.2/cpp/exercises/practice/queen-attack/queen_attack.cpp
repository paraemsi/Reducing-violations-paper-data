#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos(white), black_pos(black)
{
    // Check white queen position is on the board
    if (white.first < 0 || white.first > 7 || white.second < 0 || white.second > 7) {
        throw std::domain_error("White queen position is off the board");
    }
    // Check black queen position is on the board
    if (black.first < 0 || black.first > 7 || black.second < 0 || black.second > 7) {
        throw std::domain_error("Black queen position is off the board");
    }
    // Check that queens are not on the same square
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Same row
    if (white_pos.first == black_pos.first) return true;
    // Same column
    if (white_pos.second == black_pos.second) return true;
    // Same diagonal
    if (std::abs(white_pos.first - black_pos.first) == std::abs(white_pos.second - black_pos.second)) return true;
    return false;
}

}  // namespace queen_attack
