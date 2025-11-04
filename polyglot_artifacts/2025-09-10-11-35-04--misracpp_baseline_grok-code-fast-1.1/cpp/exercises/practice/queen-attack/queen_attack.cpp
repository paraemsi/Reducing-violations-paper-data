#include "queen_attack.h"
#include <utility>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) {
    if (white.first < 0 || white.first > 7 || white.second < 0 || white.second > 7 ||
        black.first < 0 || black.first > 7 || black.second < 0 || black.second > 7) {
        throw std::domain_error("Position out of bounds");
    }
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    white_pos = white;
    black_pos = black;
}

bool chess_board::can_attack() const {
    int row1 = white_pos.first;
    int col1 = white_pos.second;
    int row2 = black_pos.first;
    int col2 = black_pos.second;

    // Same row
    if (row1 == row2) return true;
    // Same column
    if (col1 == col2) return true;
    // Same diagonal
    if (std::abs(row1 - row2) == std::abs(col1 - col2)) return true;
    return false;
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

}  // namespace queen_attack
