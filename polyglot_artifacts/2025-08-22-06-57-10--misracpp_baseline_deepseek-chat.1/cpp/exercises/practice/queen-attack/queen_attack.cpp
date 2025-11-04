#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <utility>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(white), black_pos(black) {
    // Check if positions are valid (0-7)
    if (white_pos.first < 0 || white_pos.first > 7 || 
        white_pos.second < 0 || white_pos.second > 7 ||
        black_pos.first < 0 || black_pos.first > 7 || 
        black_pos.second < 0 || black_pos.second > 7) {
        throw std::domain_error("Invalid position");
    }
    // Check if positions are the same
    if (white_pos == black_pos) {
        throw std::domain_error("Both queens cannot be placed on the same square");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    int dx = white_pos.first - black_pos.first;
    int dy = white_pos.second - black_pos.second;
    
    // Check if on the same row, column, or diagonal
    return (dx == 0) || (dy == 0) || (std::abs(dx) == std::abs(dy));
}

}  // namespace queen_attack
