#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <string>

namespace queen_attack {

chess_board::chess_board(std::pair<std::int8_t, std::int8_t> white, std::pair<std::int8_t, std::int8_t> black) 
    : white_pos(white), black_pos(black) {
    // Validate positions are within the board
    if ((white_pos.first < 0) || (white_pos.first > 7) || 
        (white_pos.second < 0) || (white_pos.second > 7) ||
        (black_pos.first < 0) || (black_pos.first > 7) || 
        (black_pos.second < 0) || (black_pos.second > 7)) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
    if ((white_pos.first == black_pos.first) && (white_pos.second == black_pos.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<std::int8_t, std::int8_t> chess_board::white() const {
    return white_pos;
}

std::pair<std::int8_t, std::int8_t> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Cast to int to avoid issues with std::int8_t and std::abs
    if (std::abs(static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first)) == 
        std::abs(static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
