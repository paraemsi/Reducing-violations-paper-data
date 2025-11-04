#include "queen_attack.h"
#include <stdexcept>
#include <utility>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_pos(white), black_pos(black) {
    // Check if positions are on the board
    if (white_pos.first < 0 || white_pos.first > 7 || white_pos.second < 0 || white_pos.second > 7 ||
        black_pos.first < 0 || black_pos.first > 7 || black_pos.second < 0 || black_pos.second > 7) {
        throw std::domain_error("Queen position must be on a 8x8 board");
    }
    // Check if positions are the same
    if (white_pos == black_pos) {
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
    int x1 = white_pos.first;
    int y1 = white_pos.second;
    int x2 = black_pos.first;
    int y2 = black_pos.second;

    // Same row
    if (y1 == y2) return true;
    // Same column
    if (x1 == x2) return true;
    // Same diagonal
    if (std::abs(x1 - x2) == std::abs(y1 - y2)) return true;

    return false;
}

}  // namespace queen_attack
