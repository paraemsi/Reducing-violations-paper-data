#include "queen_attack.h"
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

chess_board::chess_board(position_t white, position_t black)
    : white_pos(std::make_pair(static_cast<coord_t>(white.first), 
                               static_cast<coord_t>(white.second))),
      black_pos(std::make_pair(static_cast<coord_t>(black.first), 
                               static_cast<coord_t>(black.second))) {
    // Validate positions are within the chessboard
    auto is_valid = [](const std::pair<coord_t, coord_t>& pos) {
        return (pos.first >= static_cast<coord_t>(0)) && 
               (pos.first < static_cast<coord_t>(8)) && 
               (pos.second >= static_cast<coord_t>(0)) && 
               (pos.second < static_cast<coord_t>(8));
    };
    
    if (!is_valid(white_pos) || !is_valid(black_pos)) {
        throw std::domain_error("Invalid queen position: must be within the chessboard");
    }
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

position_t chess_board::white() const {
    return std::make_pair(static_cast<int>(white_pos.first), 
                          static_cast<int>(white_pos.second));
}

position_t chess_board::black() const {
    return std::make_pair(static_cast<int>(black_pos.first), 
                          static_cast<int>(black_pos.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_pos.first == black_pos.first) || (white_pos.second == black_pos.second)) {
        return true;
    }
    // Check if on the same diagonal
    // Add parentheses according to MISRA rules
    int row_diff = static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first);
    int col_diff = static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second);
    if ((std::abs(row_diff) == std::abs(col_diff))) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
