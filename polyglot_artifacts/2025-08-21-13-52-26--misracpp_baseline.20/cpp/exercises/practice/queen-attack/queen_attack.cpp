#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos_{white}, black_pos_{black} {
    // Check if positions are on the board
    auto valid = [](std::pair<int, int> pos) {
        return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
    };
    if (!valid(white) || !valid(black)) {
        throw std::domain_error("Queen position must be on a standard 8x8 chessboard.");
    }
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

    // Same row, same column, or same diagonal
    return (row1 == row2) ||
           (col1 == col2) ||
           (std::abs(row1 - row2) == std::abs(col1 - col2));
}

}  // namespace queen_attack
