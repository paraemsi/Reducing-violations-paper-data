#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<coordinate_t, coordinate_t> white, std::pair<coordinate_t, coordinate_t> black) 
    : white_pos(static_cast<std::int8_t>(white.first), static_cast<std::int8_t>(white.second)),
      black_pos(static_cast<std::int8_t>(black.first), static_cast<std::int8_t>(black.second)) {
    // Check if queens are on the same position
    if ((white_pos.first == black_pos.first) && (white_pos.second == black_pos.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7 for both coordinates)
    if (((white.first) < 0) || ((white.first) > 7) || 
        ((white.second) < 0) || ((white.second) > 7) ||
        ((black.first) < 0) || ((black.first) > 7) || 
        ((black.second) < 0) || ((black.second) > 7)) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
}

std::pair<coordinate_t, coordinate_t> chess_board::white() const {
    return std::make_pair(static_cast<coordinate_t>(white_pos.first), 
                          static_cast<coordinate_t>(white_pos.second));
}

std::pair<coordinate_t, coordinate_t> chess_board::black() const {
    return std::make_pair(static_cast<coordinate_t>(black_pos.first), 
                          static_cast<coordinate_t>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal (|Δx| == |Δy|)
    // Use parentheses to ensure proper precedence
    const coordinate_t delta_x = static_cast<coordinate_t>(white_pos.first) - 
                                 static_cast<coordinate_t>(black_pos.first);
    const coordinate_t delta_y = static_cast<coordinate_t>(white_pos.second) - 
                                 static_cast<coordinate_t>(black_pos.second);
    if ((std::abs(delta_x)) == (std::abs(delta_y))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
