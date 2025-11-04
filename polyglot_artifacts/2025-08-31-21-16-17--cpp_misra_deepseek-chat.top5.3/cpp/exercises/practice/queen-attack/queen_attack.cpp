#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(static_cast<coord_t>(white.first), 
                static_cast<coord_t>(white.second)),
      black_pos(static_cast<coord_t>(black.first), 
                static_cast<coord_t>(black.second)) {
    // Check if queens are on the same position
    if (((white_pos.first == black_pos.first)) && ((white_pos.second == black_pos.second))) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7)
    // Ensure all conditions are properly parenthesized
    if (((white_pos.first < 0) || (white_pos.first >= 8)) || 
        ((white_pos.second < 0) || (white_pos.second >= 8)) ||
        ((black_pos.first < 0) || (black_pos.first >= 8)) || 
        ((black_pos.second < 0) || (black_pos.second >= 8))) {
        throw std::domain_error("Position out of bounds");
    }
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), 
                          static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), 
                          static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (((white_pos.first == black_pos.first)) || ((white_pos.second == black_pos.second))) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Cast to int to avoid potential issues with std::abs and coord_t
    int row_diff = (static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first));
    int col_diff = (static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second));
    if ((std::abs(row_diff)) == (std::abs(col_diff))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
