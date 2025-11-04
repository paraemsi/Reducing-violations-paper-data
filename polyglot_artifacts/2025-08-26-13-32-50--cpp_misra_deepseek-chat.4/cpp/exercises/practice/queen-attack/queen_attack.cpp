#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<std::int32_t, std::int32_t> white, std::pair<std::int32_t, std::int32_t> black) 
    : white_position(white), black_position(black) {
    // Check if positions are valid
    if ((white_position.first < 0) || (white_position.first >= 8) ||
        (white_position.second < 0) || (white_position.second >= 8) ||
        (black_position.first < 0) || (black_position.first >= 8) ||
        (black_position.second < 0) || (black_position.second >= 8)) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
    // Check if queens are on the same square
    if ((white_position.first == black_position.first) && (white_position.second == black_position.second)) {
        throw std::domain_error("Invalid queen position: queens cannot be on the same square");
    }
}

std::pair<std::int32_t, std::int32_t> chess_board::white() const {
    return white_position;
}

std::pair<std::int32_t, std::int32_t> chess_board::black() const {
    return black_position;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_position.first == black_position.first) || 
        (white_position.second == black_position.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    std::int32_t row_diff = (white_position.first - black_position.first);
    std::int32_t col_diff = (white_position.second - black_position.second);
    if (std::abs(row_diff) == std::abs(col_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
