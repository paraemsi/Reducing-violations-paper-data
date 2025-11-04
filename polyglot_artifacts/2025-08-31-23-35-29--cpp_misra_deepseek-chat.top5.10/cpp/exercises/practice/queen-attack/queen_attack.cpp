#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace queen_attack {

namespace {
    coord_t parse_file(char c) {
        switch(c) {
            case 'a': return 0;
            case 'b': return 1;
            case 'c': return 2;
            case 'd': return 3;
            case 'e': return 4;
            case 'f': return 5;
            case 'g': return 6;
            case 'h': return 7;
            default: throw std::domain_error("Invalid file");
        }
    }

    coord_t parse_rank(char c) {
        switch(c) {
            case '1': return 7;
            case '2': return 6;
            case '3': return 5;
            case '4': return 4;
            case '5': return 3;
            case '6': return 2;
            case '7': return 1;
            case '8': return 0;
            default: throw std::domain_error("Invalid rank");
        }
    }
}

chess_board::chess_board(const std::string& white, const std::string& black) {
    // Parse white position
    if (white.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    coord_t white_col = parse_file(white[0]);
    coord_t white_row = parse_rank(white[1]);
    white_position = std::make_pair(white_col, white_row);
    
    // Parse black position
    if (black.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    coord_t black_col = parse_file(black[0]);
    coord_t black_row = parse_rank(black[1]);
    black_position = std::make_pair(black_col, black_row);
    
    // Check if queens are on the same square
    if ((white_position.first == black_position.first) && (white_position.second == black_position.second)) {
        throw std::domain_error("Queens cannot be on the same square");
    }
}

std::pair<coord_t, coord_t> chess_board::white() const {
    return white_position;
}

std::pair<coord_t, coord_t> chess_board::black() const {
    return black_position;
}

bool chess_board::can_attack() const {
    // Check if they are in the same row or column
    if ((white_position.first == black_position.first) || 
        (white_position.second == black_position.second)) {
        return true;
    }
    // Check if they are on the same diagonal
    // Use absolute differences
    const coord_t row_diff = (white_position.first > black_position.first) 
        ? (white_position.first - black_position.first) 
        : (black_position.first - white_position.first);
    const coord_t col_diff = (white_position.second > black_position.second) 
        ? (white_position.second - black_position.second) 
        : (black_position.second - white_position.second);
    if (row_diff == col_diff) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
