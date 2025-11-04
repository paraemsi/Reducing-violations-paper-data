#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos_{white}, black_pos_{black} {
    // Check bounds
    if (white.first < 0 || white.first > 7 || white.second < 0 || white.second > 7 ||
        black.first < 0 || black.first > 7 || black.second < 0 || black.second > 7) {
        throw std::domain_error("Queen position must be on a standard 8x8 chessboard.");
    }
    // Check for same position
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same position.");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos_;
}

std::pair<int, int> chess_board::black() const {
    return black_pos_;
}

bool chess_board::can_attack() const {
    int row1 = white_pos_.first;
    int col1 = white_pos_.second;
    int row2 = black_pos_.first;
    int col2 = black_pos_.second;

    // Same row
    if (row1 == row2) return true;
    // Same column
    if (col1 == col2) return true;
    // Same diagonal
    if (std::abs(row1 - row2) == std::abs(col1 - col2)) return true;

    return false;
}

}  // namespace queen_attack
