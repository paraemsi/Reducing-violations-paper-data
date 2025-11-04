#include "queen_attack.h"
#include <utility>
#include <cmath>
#include <cstdint>
#include <string>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black) {
    // Check if positions are valid (on an 8x8 board)
    if ((white.first < 0) || (white.first >= 8) || 
        (white.second < 0) || (white.second >= 8) ||
        (black.first < 0) || (black.first >= 8) || 
        (black.second < 0) || (black.second >= 8)) {
        throw std::domain_error("Positions must be on the chessboard");
    }
    // Check if queens are on the same square
    if ((white.first == black.first) && (white.second == black.second)) {
        throw std::domain_error("Queens cannot be on the same square");
    }
    
    // Assign with explicit casts
    white_pos.first = static_cast<std::int8_t>(white.first);
    white_pos.second = static_cast<std::int8_t>(white.second);
    black_pos.first = static_cast<std::int8_t>(black.first);
    black_pos.second = static_cast<std::int8_t>(black.second);
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
    // Cast to int to avoid potential issues with std::abs and int8_t
    // Use parentheses to ensure proper operator precedence
    int delta_x = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    int delta_y = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    if (std::abs(delta_x) == std::abs(delta_y)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
