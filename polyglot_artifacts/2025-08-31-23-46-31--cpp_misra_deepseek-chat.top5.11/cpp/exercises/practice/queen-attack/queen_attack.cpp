#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <map>

namespace queen_attack {

chess_board::chess_board(const std::string& white, const std::string& black) {
    // Parse white position
    if (white.size() != 2) { 
        throw std::domain_error("Invalid position");
    }
    
    // Map column letter to index
    static const std::map<char, int> col_map = {
        {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3},
        {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}
    };
    
    // Map row digit to index
    static const std::map<char, int> row_map = {
        {'1', 0}, {'2', 1}, {'3', 2}, {'4', 3},
        {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}
    };
    
    // Parse white column
    auto white_col_it = col_map.find(white[0]);
    if (white_col_it == col_map.end()) { 
        throw std::domain_error("Invalid position");
    }
    int white_col = white_col_it->second;
    
    // Parse white row
    auto white_row_it = row_map.find(white[1]);
    if (white_row_it == row_map.end()) { 
        throw std::domain_error("Invalid position");
    }
    int white_row = white_row_it->second;
    
    // Parse black position
    if (black.size() != 2) { 
        throw std::domain_error("Invalid position");
    }
    
    // Parse black column
    auto black_col_it = col_map.find(black[0]);
    if (black_col_it == col_map.end()) { 
        throw std::domain_error("Invalid position");
    }
    int black_col = black_col_it->second;
    
    // Parse black row
    auto black_row_it = row_map.find(black[1]);
    if (black_row_it == row_map.end()) { 
        throw std::domain_error("Invalid position");
    }
    int black_row = black_row_it->second;
    
    // Set positions
    white_pos = std::make_pair(white_row, white_col);
    black_pos = std::make_pair(black_row, black_col);
    
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
    int row_diff = white_pos.first - black_pos.first;
    int col_diff = white_pos.second - black_pos.second;
    if (row_diff < 0) {
        row_diff = -row_diff;
    }
    if (col_diff < 0) {
        col_diff = -col_diff;
    }
    if (row_diff == col_diff) { 
        return true;
    }
    return false;
}

}  // namespace queen_attack
