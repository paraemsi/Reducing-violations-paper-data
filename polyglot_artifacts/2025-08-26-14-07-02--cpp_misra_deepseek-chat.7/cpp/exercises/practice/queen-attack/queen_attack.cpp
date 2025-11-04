#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(position_t(static_cast<coordinate_t>(white.first), 
                           static_cast<coordinate_t>(white.second))),
      black_pos(position_t(static_cast<coordinate_t>(black.first), 
                           static_cast<coordinate_t>(black.second))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7 for both coordinates)
    // Add parentheses according to MISRA rules
    if ((((white_pos.first < 0) || (white_pos.first > 7)) || 
         ((white_pos.second < 0) || (white_pos.second > 7))) ||
        (((black_pos.first < 0) || (black_pos.first > 7)) || 
         ((black_pos.second < 0) || (black_pos.second > 7)))) {
        throw std::domain_error("Position out of bounds");
    }
}

std::pair<int, int> chess_board::white() const {
    // Use static_cast to convert from fixed-width to int
    return std::pair<int, int>(static_cast<int>(white_pos.first), 
                               static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    // Use static_cast to convert from fixed-width to int
    return std::pair<int, int>(static_cast<int>(black_pos.first), 
                               static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if (((white_pos.first == black_pos.first)) || ((white_pos.second == black_pos.second))) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    // Add parentheses to ensure proper precedence
    coordinate_t delta_x = (white_pos.first - black_pos.first);
    coordinate_t delta_y = (white_pos.second - black_pos.second);
    if ((std::abs(delta_x)) == (std::abs(delta_y))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
