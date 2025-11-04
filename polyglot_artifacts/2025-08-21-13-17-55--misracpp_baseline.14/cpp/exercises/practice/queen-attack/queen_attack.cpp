#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

queen::queen(int row, int col) : row_{row}, col_{col} {
    if (row < 0 || row > 7 || col < 0 || col > 7) {
        throw std::domain_error("Queen position must be on a standard 8x8 chessboard.");
    }
}

std::pair<int, int> queen::position() const {
    return {row_, col_};
}

bool can_attack(const queen& q1, const queen& q2) {
    auto [row1, col1] = q1.position();
    auto [row2, col2] = q2.position();

    if (row1 == row2 && col1 == col2) {
        // Same position, cannot attack itself
        return false;
    }

    // Same row, same column, or same diagonal
    return (row1 == row2) ||
           (col1 == col2) ||
           (std::abs(row1 - row2) == std::abs(col1 - col2));
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_pos_{white}, black_pos_{black} {
    // Check for out-of-bounds
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

    // Same row, same column, or same diagonal
    return (row1 == row2) ||
           (col1 == col2) ||
           (std::abs(row1 - row2) == std::abs(col1 - col2));
}

}  // namespace queen_attack
