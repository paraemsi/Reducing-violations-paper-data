#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <string>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(const std::pair<int, int>& white, const std::pair<int, int>& black) {
    // Convert to int8_t
    white_pos = std::make_pair(static_cast<std::int8_t>(white.first), static_cast<std::int8_t>(white.second));
    black_pos = std::make_pair(static_cast<std::int8_t>(black.first), static_cast<std::int8_t>(black.second));
    // Check if positions are valid (0-7 for both coordinates)
    // Add parentheses to follow operator precedence rules
    if (((white_pos.first < 0) || (white_pos.first > 7)) || 
        ((white_pos.second < 0) || (white_pos.second > 7)) ||
        ((black_pos.first < 0) || (black_pos.first > 7)) || 
        ((black_pos.second < 0) || (black_pos.second > 7))) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
    // Check if queens are on the same square
    if (((white_pos.first == black_pos.first)) && ((white_pos.second == black_pos.second))) {
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
    if (((white_pos.first == black_pos.first)) || ((white_pos.second == black_pos.second))) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Add parentheses to follow operator precedence rules
    int dx = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    int dy = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    if ((std::abs(dx)) == (std::abs(dy))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
