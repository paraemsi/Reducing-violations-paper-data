#include "queen_attack.h"
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <string>

namespace queen_attack {

chess_board::chess_board() 
    : white_pos(parse_position("a1")), 
      black_pos(parse_position("a8")) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be placed on the same square");
    }
}

chess_board::chess_board(const std::string& white, const std::string& black)
    : white_pos(parse_position(white)), 
      black_pos(parse_position(black)) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be placed on the same square");
    }
}

std::pair<coordinate_t, coordinate_t> chess_board::parse_position(const std::string& pos) {
    if (pos.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char col_char = pos[0];
    char row_char = pos[1];
    
    if (((col_char < 'a') || (col_char > 'h') || (row_char < '1') || (row_char > '8'))) {
        throw std::domain_error("Invalid position");
    }
    
    coordinate_t col = static_cast<coordinate_t>(col_char - 'a');
    coordinate_t row = static_cast<coordinate_t>((8 - static_cast<int>((row_char - '0'))));
    return std::make_pair(col, row);
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), 
                          static_cast<int>(white_pos.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), 
                          static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal
    // Cast to int to avoid issues with std::abs and int8_t
    int col_diff = (static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first));
    int row_diff = (static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second));
    if (std::abs(col_diff) == std::abs(row_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
