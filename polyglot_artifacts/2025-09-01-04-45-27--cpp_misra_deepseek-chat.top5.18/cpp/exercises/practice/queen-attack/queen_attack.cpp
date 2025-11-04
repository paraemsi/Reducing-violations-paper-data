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
        throw std::domain_error("Invalid queen position: position must be two characters");
    }
    
    // Check column is between 'a' and 'h' using allowed equality comparisons
    const char white_col = white[0];
    bool valid_white_col = false;
    if ((white_col == 'a') || (white_col == 'b') || (white_col == 'c') || (white_col == 'd') || 
        (white_col == 'e') || (white_col == 'f') || (white_col == 'g') || (white_col == 'h')) {
        valid_white_col = true;
    }
    
    // Check row is between '1' and '8'
    const char white_row = white[1];
    bool valid_white_row = false;
    if ((white_row == '1') || (white_row == '2') || (white_row == '3') || (white_row == '4') || 
        (white_row == '5') || (white_row == '6') || (white_row == '7') || (white_row == '8')) {
        valid_white_row = true;
    }
    
    if (!valid_white_col || !valid_white_row) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
    
    // Map to coordinates
    int col_map_white = 0;
    if (white_col == 'a') col_map_white = 0;
    else if (white_col == 'b') col_map_white = 1;
    else if (white_col == 'c') col_map_white = 2;
    else if (white_col == 'd') col_map_white = 3;
    else if (white_col == 'e') col_map_white = 4;
    else if (white_col == 'f') col_map_white = 5;
    else if (white_col == 'g') col_map_white = 6;
    else if (white_col == 'h') col_map_white = 7;
    
    int row_map_white = 0;
    if (white_row == '1') row_map_white = 7;
    else if (white_row == '2') row_map_white = 6;
    else if (white_row == '3') row_map_white = 5;
    else if (white_row == '4') row_map_white = 4;
    else if (white_row == '5') row_map_white = 3;
    else if (white_row == '6') row_map_white = 2;
    else if (white_row == '7') row_map_white = 1;
    else if (white_row == '8') row_map_white = 0;
    
    white_pos.first = col_map_white;
    white_pos.second = row_map_white;
    
    // Parse black position
    if (black.size() != 2) {
        throw std::domain_error("Invalid queen position: position must be two characters");
    }
    
    const char black_col = black[0];
    bool valid_black_col = false;
    if ((black_col == 'a') || (black_col == 'b') || (black_col == 'c') || (black_col == 'd') || 
        (black_col == 'e') || (black_col == 'f') || (black_col == 'g') || (black_col == 'h')) {
        valid_black_col = true;
    }
    
    const char black_row = black[1];
    bool valid_black_row = false;
    if ((black_row == '1') || (black_row == '2') || (black_row == '3') || (black_row == '4') || 
        (black_row == '5') || (black_row == '6') || (black_row == '7') || (black_row == '8')) {
        valid_black_row = true;
    }
    
    if (!valid_black_col || !valid_black_row) {
        throw std::domain_error("Invalid queen position: position must be on the board");
    }
    
    int col_map_black = 0;
    if (black_col == 'a') col_map_black = 0;
    else if (black_col == 'b') col_map_black = 1;
    else if (black_col == 'c') col_map_black = 2;
    else if (black_col == 'd') col_map_black = 3;
    else if (black_col == 'e') col_map_black = 4;
    else if (black_col == 'f') col_map_black = 5;
    else if (black_col == 'g') col_map_black = 6;
    else if (black_col == 'h') col_map_black = 7;
    
    int row_map_black = 0;
    if (black_row == '1') row_map_black = 7;
    else if (black_row == '2') row_map_black = 6;
    else if (black_row == '3') row_map_black = 5;
    else if (black_row == '4') row_map_black = 4;
    else if (black_row == '5') row_map_black = 3;
    else if (black_row == '6') row_map_black = 2;
    else if (black_row == '7') row_map_black = 1;
    else if (black_row == '8') row_map_black = 0;
    
    black_pos.first = col_map_black;
    black_pos.second = row_map_black;
    
    if ((white_pos.first == black_pos.first) && (white_pos.second == black_pos.second)) {
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
    // Calculate differences
    const int row_diff = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    const int col_diff = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    // Take absolute values and compare
    if ((std::abs(row_diff)) == (std::abs(col_diff))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
