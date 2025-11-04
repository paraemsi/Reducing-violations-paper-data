#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, 
                         const std::pair<int, int>& black) 
    : white_pos(white), black_pos(black) {
    // Check if positions are valid
    if ((white_pos.first < 0) || (white_pos.first >= 8) || 
        (white_pos.second < 0) || (white_pos.second >= 8) ||
        (black_pos.first < 0) || (black_pos.first >= 8) || 
        (black_pos.second < 0) || (black_pos.second >= 8)) {
        throw std::domain_error("Invalid position");
    }
    // Check if queens are on the same square
    if ((white_pos.first == black_pos.first) && (white_pos.second == black_pos.second)) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    if (std::abs(white_pos.first - black_pos.first) == std::abs(white_pos.second - black_pos.second)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
