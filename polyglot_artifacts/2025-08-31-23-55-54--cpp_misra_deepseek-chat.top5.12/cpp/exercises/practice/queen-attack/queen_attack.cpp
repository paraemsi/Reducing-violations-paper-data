#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(const std::string& white, const std::string& black) {
    // Parse white position
    if (white.size() != 2) {
        throw std::domain_error("Invalid queen position");
    }
    
    // Convert column letter to number using a string find
    const std::string valid_columns = "abcdefgh";
    std::size_t white_col_index = valid_columns.find(white[0]);
    if (white_col_index == std::string::npos) {
        throw std::domain_error("Invalid queen position");
    }
    
    // Convert row digit
    const std::string valid_rows = "12345678";
    std::size_t white_row_index = valid_rows.find(white[1]);
    if (white_row_index == std::string::npos) {
        throw std::domain_error("Invalid queen position");
    }
    coordinate_t white_col = static_cast<coordinate_t>(white_col_index);
    // Rows are 1-8, we want 0-7 from the top, so 7 - index
    coordinate_t white_row = static_cast<coordinate_t>(7 - white_row_index);
    
    // Parse black position
    if (black.size() != 2) {
        throw std::domain_error("Invalid queen position");
    }
    
    std::size_t black_col_index = valid_columns.find(black[0]);
    if (black_col_index == std::string::npos) {
        throw std::domain_error("Invalid queen position");
    }
    
    std::size_t black_row_index = valid_rows.find(black[1]);
    if (black_row_index == std::string::npos) {
        throw std::domain_error("Invalid queen position");
    }
    coordinate_t black_col = static_cast<coordinate_t>(black_col_index);
    coordinate_t black_row = static_cast<coordinate_t>(7 - black_row_index);
    
    // Check if positions are the same
    if ((white_col == black_col) && (white_row == black_row)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    
    white_pos = std::make_pair(white_col, white_row);
    black_pos = std::make_pair(black_col, black_row);
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
    // Use absolute differences
    // Cast to int to avoid issues with std::abs and int8_t
    int delta_x = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    int delta_y = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    if (std::abs(delta_x) == std::abs(delta_y)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
