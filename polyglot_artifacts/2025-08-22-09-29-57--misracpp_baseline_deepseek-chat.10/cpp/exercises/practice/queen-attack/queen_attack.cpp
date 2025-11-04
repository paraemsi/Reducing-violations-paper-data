#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <utility>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(white), black_pos(black) {
    // Check if positions are valid (0-7)
    if (white.first < 0 || white.first > 7 || white.second < 0 || white.second > 7) {
        throw std::domain_error("Invalid white queen position");
    }
    if (black.first < 0 || black.first > 7 || black.second < 0 || black.second > 7) {
        throw std::domain_error("Invalid black queen position");
    }
    if (white == black) {
        throw std::domain_error("Queen positions must be distinct");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    int col_diff = std::abs(white_pos.first - black_pos.first);
    int row_diff = std::abs(white_pos.second - black_pos.second);
    
    // Check if on the same row, column, or diagonal
    return (col_diff == 0) || (row_diff == 0) || (col_diff == row_diff);
}

}  // namespace queen_attack
