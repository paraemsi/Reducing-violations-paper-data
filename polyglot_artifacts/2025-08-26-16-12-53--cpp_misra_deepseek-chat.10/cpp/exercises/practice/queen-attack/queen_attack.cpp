#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <cctype>
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

chess_board::chess_board(position_t white, position_t black)
    : white_pos(std::make_pair(static_cast<coordinate_t>(white.first), 
                               static_cast<coordinate_t>(white.second))),
      black_pos(std::make_pair(static_cast<coordinate_t>(black.first), 
                               static_cast<coordinate_t>(black.second))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7)
    // Since coordinate_t is now unsigned, we only need to check the upper bound
    if ((white.first > 7) || (white.second > 7) ||
        (black.first > 7) || (black.second > 7) ||
        (white.first < 0) || (white.second < 0) ||
        (black.first < 0) || (black.second < 0)) {
        throw std::domain_error("Invalid queen position");
    }
}

position_t chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), 
                          static_cast<int>(white_pos.second));
}

position_t chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), 
                          static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check diagonals: difference in x equals difference in y
    // Cast to int to avoid potential issues with std::abs and coordinate_t
    // Since coordinates are unsigned, we need to ensure no underflow when subtracting
    int delta_x = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    int delta_y = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    if (std::abs(delta_x) == std::abs(delta_y)) {
        return true;
    }
    return false;
}

chess_board::operator std::string() const {
    std::stringstream board;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i == static_cast<int>(white_pos.first)) && (j == static_cast<int>(white_pos.second))) {
                board << 'W';
            } else if ((i == static_cast<int>(black_pos.first)) && (j == static_cast<int>(black_pos.second))) {
                board << 'B';
            } else {
                board << '_';
            }
            if (j < 7) {
                board << ' ';
            }
        }
        board << '\n';
    }
    return board.str();
}

}  // namespace queen_attack
