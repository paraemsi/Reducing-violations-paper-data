#include "queen_attack.h"
#include <stdexcept>
#include <algorithm>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black)
    : white_pos_{white}, black_pos_{black} {
    // Check for out-of-bounds
    auto valid = [](const std::pair<int, int>& pos) {
        return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
    };
    if (!valid(white) || !valid(black)) {
        throw std::domain_error("Queen position out of bounds");
    }
    if (white == black) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const noexcept {
    return white_pos_;
}

std::pair<int, int> chess_board::black() const noexcept {
    return black_pos_;
}

bool chess_board::can_attack() const noexcept {
    int row1 = white_pos_.first, col1 = white_pos_.second;
    int row2 = black_pos_.first, col2 = black_pos_.second;
    // Same row
    if (row1 == row2) return true;
    // Same column
    if (col1 == col2) return true;
    // Same diagonal
    if (std::abs(row1 - row2) == std::abs(col1 - col2)) return true;
    return false;
}

}  // namespace queen_attack
