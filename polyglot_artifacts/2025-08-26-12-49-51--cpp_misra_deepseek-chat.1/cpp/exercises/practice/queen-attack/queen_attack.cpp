#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
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

chess_board::chess_board(const std::string& white, const std::string& black)
    : white_pos(parse_position(white)), black_pos(parse_position(black)) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<coord_t, coord_t> chess_board::parse_position(const std::string& pos) const {
    if (pos.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    
    char col_char = pos[0];
    char row_char = pos[1];
    
    if (col_char < 'a' || col_char > 'h' || row_char < '1' || row_char > '8') {
        throw std::domain_error("Invalid position");
    }
    
    coord_t col = static_cast<coord_t>(col_char - 'a');
    coord_t row = static_cast<coord_t>(7 - (row_char - '1'));
    
    return std::make_pair(col, row);
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
    // Use the coord_t type for differences
    coord_t row_diff = white_pos.first - black_pos.first;
    coord_t col_diff = white_pos.second - black_pos.second;
    
    // Take absolute values using a type that works with std::abs
    // Since coord_t is an alias for int, this is fine
    if (std::abs(row_diff) == std::abs(col_diff)) {
        return true;
    }
    
    return false;
}

}  // namespace queen_attack
