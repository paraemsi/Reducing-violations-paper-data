#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cctype>
#include <cstdint>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(position_t white, position_t black) {
    // Convert to internal types
    white_queen_.first = static_cast<coord_type>(white.first);
    white_queen_.second = static_cast<coord_type>(white.second);
    black_queen_.first = static_cast<coord_type>(black.first);
    black_queen_.second = static_cast<coord_type>(black.second);
    
    if (white_queen_ == black_queen_) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
    // Check if positions are valid (0-7)
    if ((white_queen_.first < 0) || (white_queen_.first > 7) || 
        (white_queen_.second < 0) || (white_queen_.second > 7) ||
        (black_queen_.first < 0) || (black_queen_.first > 7) || 
        (black_queen_.second < 0) || (black_queen_.second > 7)) {
        throw std::domain_error("Invalid queen position");
    }
}

chess_board::chess_board() 
    : white_queen_(std::make_pair(static_cast<coord_type>(0), static_cast<coord_type>(3))), 
      black_queen_(std::make_pair(static_cast<coord_type>(7), static_cast<coord_type>(3))) {}

chess_board::chess_board(const std::pair<std::string, std::string>& positions) {
    // Parse white position
    if (positions.first.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char white_col = positions.first[0];
    char white_row = positions.first[1];
    
    if ((white_col < 'a') || (white_col > 'h') || (white_row < '1') || (white_row > '8')) {
        throw std::domain_error("Invalid position");
    }
    white_queen_.first = static_cast<coord_type>(8 - (white_row - '0'));
    white_queen_.second = static_cast<coord_type>(white_col - 'a');
    
    // Parse black position
    if (positions.second.size() != 2) {
        throw std::domain_error("Invalid position");
    }
    char black_col = positions.second[0];
    char black_row = positions.second[1];
    
    if ((black_col < 'a') || (black_col > 'h') || (black_row < '1') || (black_row > '8')) {
        throw std::domain_error("Invalid position");
    }
    black_queen_.first = static_cast<coord_type>(8 - (black_row - '0'));
    black_queen_.second = static_cast<coord_type>(black_col - 'a');
    
    if (white_queen_ == black_queen_) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position_t chess_board::white() const {
    return std::make_pair(static_cast<int>(white_queen_.first), 
                          static_cast<int>(white_queen_.second));
}

position_t chess_board::black() const {
    return std::make_pair(static_cast<int>(black_queen_.first), 
                          static_cast<int>(black_queen_.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_queen_.first == black_queen_.first) || 
        (white_queen_.second == black_queen_.second)) {
        return true;
    }
    // Check if on the same diagonal
    int row_diff = static_cast<int>(white_queen_.first) - static_cast<int>(black_queen_.first);
    int col_diff = static_cast<int>(white_queen_.second) - static_cast<int>(black_queen_.second);
    if (std::abs(row_diff) == std::abs(col_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
