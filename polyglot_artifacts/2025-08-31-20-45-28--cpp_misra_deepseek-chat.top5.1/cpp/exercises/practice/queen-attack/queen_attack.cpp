#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board() 
    : white_pos(std::make_pair(static_cast<coordinate_t>(0), static_cast<coordinate_t>(3))), 
      black_pos(std::make_pair(static_cast<coordinate_t>(7), static_cast<coordinate_t>(3))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black) {
    // Check if positions are valid (0-7)
    if ((white.first < 0) || (white.first > 7) || 
        (white.second < 0) || (white.second > 7) ||
        (black.first < 0) || (black.first > 7) || 
        (black.second < 0) || (black.second > 7)) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
    
    // Convert to coordinate_t for internal storage
    white_pos = std::make_pair(static_cast<coordinate_t>(white.first), 
                               static_cast<coordinate_t>(white.second));
    black_pos = std::make_pair(static_cast<coordinate_t>(black.first), 
                               static_cast<coordinate_t>(black.second));
    
    // Check if queens are on the same position
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Cast to int to avoid issues with std::abs and coordinate_t
    int row_diff = (static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first));
    int col_diff = (static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second));
    if (std::abs(row_diff) == std::abs(col_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
