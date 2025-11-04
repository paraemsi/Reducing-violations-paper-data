#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board() 
    : white_pos(std::make_pair(static_cast<coord_t>(0), static_cast<coord_t>(3))), 
      black_pos(std::make_pair(static_cast<coord_t>(7), static_cast<coord_t>(3))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::chess_board(std::pair<coord_t, coord_t> white, std::pair<coord_t, coord_t> black)
    : white_pos(white), black_pos(black) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7)
    if ((white_pos.first < 0) || (white_pos.first > 7) || 
        (white_pos.second < 0) || (white_pos.second > 7) ||
        (black_pos.first < 0) || (black_pos.first > 7) || 
        (black_pos.second < 0) || (black_pos.second > 7)) {
        throw std::domain_error("Invalid queen position: must be on the board");
    }
}

std::pair<coord_t, coord_t> chess_board::white() const {
    return white_pos;
}

std::pair<coord_t, coord_t> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal (absolute differences are equal)
    if (std::abs(white_pos.first - black_pos.first) == std::abs(white_pos.second - black_pos.second)) {
        return true;
    }
    return false;
}

chess_board::operator std::string() const {
    std::stringstream board;
    for (coord_t i = 0; i < 8; i++) {
        for (coord_t j = 0; j < 8; j++) {
            if ((i == white_pos.first) && (j == white_pos.second)) {
                board << 'W';
            } else if ((i == black_pos.first) && (j == black_pos.second)) {
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
