#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board() 
    : white_pos(std::make_pair(static_cast<coordinate_t>(0), static_cast<coordinate_t>(3))), 
      black_pos(std::make_pair(static_cast<coordinate_t>(7), static_cast<coordinate_t>(3))) {
    // Default positions
}

chess_board::chess_board(const std::string& white, const std::string& black) {
    white_pos = parse_position(white);
    black_pos = parse_position(black);
    
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot be placed on the same position");
    }
}

std::pair<coordinate_t, coordinate_t> chess_board::parse_position(const std::string& pos) {
    if (pos.size() != 2) {
        throw std::domain_error("Invalid position format");
    }
    
    // Parse column (a-h) without using numerical values
    const std::string valid_columns = "abcdefgh";
    char col_char = pos[0];
    size_t col_index = valid_columns.find(col_char);
    if (col_index == std::string::npos) {
        throw std::domain_error("Invalid column");
    }
    coordinate_t col = static_cast<coordinate_t>(col_index);
    
    // Parse row (1-8) without using numerical values
    const std::string valid_rows = "12345678";
    char row_char = pos[1];
    size_t row_index = valid_rows.find(row_char);
    if (row_index == std::string::npos) {
        throw std::domain_error("Invalid row");
    }
    coordinate_t row = static_cast<coordinate_t>(row_index);
    
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
    if (std::abs(static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first)) == 
        std::abs(static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
