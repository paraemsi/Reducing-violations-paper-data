#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

std::pair<int, int> chess_board::parse_position(const std::string& pos) {
    if (pos.size() != 2) {
        throw std::domain_error("Invalid position format");
    }
    
    // Parse column
    char col_char = pos[0];
    if (col_char < 'a' || col_char > 'h') {
        throw std::domain_error("Invalid column");
    }
    int col = col_char - 'a';
    
    // Parse row
    char row_char = pos[1];
    if (row_char < '1' || row_char > '8') {
        throw std::domain_error("Invalid row");
    }
    int row = 8 - (row_char - '0');
    
    // Check if the parsed position is valid
    if (col < 0 || col > 7 || row < 0 || row > 7) {
        throw std::domain_error("Invalid position");
    }
    
    return std::make_pair(col, row);
}

chess_board::chess_board(const std::string& white, const std::string& black) 
    : white_pos(parse_position(white)), black_pos(parse_position(black)) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return white_pos;
}

std::pair<int, int> chess_board::black() const {
    return black_pos;
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal
    int delta_x = white_pos.first - black_pos.first;
    int delta_y = white_pos.second - black_pos.second;
    if (std::abs(delta_x) == std::abs(delta_y)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
