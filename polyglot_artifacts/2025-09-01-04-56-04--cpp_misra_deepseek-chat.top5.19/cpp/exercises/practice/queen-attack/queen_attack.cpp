#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(white), black_pos(black) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be on the same square");
    }
    // Check if positions are valid (0-7)
    if ((white_pos.first < 0) || (white_pos.first > 7) || 
        (white_pos.second < 0) || (white_pos.second > 7) ||
        (black_pos.first < 0) || (black_pos.first > 7) || 
        (black_pos.second < 0) || (black_pos.second > 7)) {
        throw std::domain_error("Invalid queen position");
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
    // Add parentheses to ensure proper precedence
    if ((std::abs(white_pos.first - black_pos.first)) == (std::abs(white_pos.second - black_pos.second))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
