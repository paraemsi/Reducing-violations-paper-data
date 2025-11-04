#include "queen_attack.h"
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white_pos, std::pair<int, int> black_pos) 
    : white_pos_(white_pos), black_pos_(black_pos) {
    // Check if queens are on the same position
    if (white_pos.first == black_pos.first && white_pos.second == black_pos.second) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos_;
}

std::pair<int, int> chess_board::black() const {
    return black_pos_;
}

bool chess_board::can_attack() const {
    // Check if on same row
    if (white_pos_.first == black_pos_.first) {
        return true;
    }
    
    // Check if on same column
    if (white_pos_.second == black_pos_.second) {
        return true;
    }
    
    // Check if on same diagonal
    // Two queens are on the same diagonal if the absolute difference
    // between their rows equals the absolute difference between their columns
    int row_diff = std::abs(white_pos_.first - black_pos_.first);
    int col_diff = std::abs(white_pos_.second - black_pos_.second);
    
    if (row_diff == col_diff) {
        return true;
    }
    
    return false;
}

}  // namespace queen_attack
