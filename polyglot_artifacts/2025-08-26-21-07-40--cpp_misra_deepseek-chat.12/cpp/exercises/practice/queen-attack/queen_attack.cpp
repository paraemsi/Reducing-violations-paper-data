#include "queen_attack.h"
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(static_cast<std::int8_t>(white.first), static_cast<std::int8_t>(white.second)),
      black_pos(static_cast<std::int8_t>(black.first), static_cast<std::int8_t>(black.second)) {
    if (white == black) {
        throw std::domain_error("Queens cannot be placed on the same square");
    }
    // Check if positions are valid (0-7)
    if (((white.first < 0) || (white.first > 7) || (white.second < 0) || (white.second > 7)) ||
        ((black.first < 0) || (black.first > 7) || (black.second < 0) || (black.second > 7))) {
        throw std::domain_error("Invalid queen position");
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
    // Use int to prevent overflow issues with std::int8_t
    int row_diff = (static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first));
    int col_diff = (static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second));
    if ((std::abs(row_diff)) == (std::abs(col_diff))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
