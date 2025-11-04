#include "queen_attack.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <sstream>

namespace queen_attack {

chess_board::chess_board() 
    : white_pos(std::make_pair(static_cast<coordinate_t>(0), 
                               static_cast<coordinate_t>(3))), 
      black_pos(std::make_pair(static_cast<coordinate_t>(7), 
                               static_cast<coordinate_t>(3))) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black) 
    : white_pos(static_cast<coordinate_t>(white.first), 
                static_cast<coordinate_t>(white.second)), 
      black_pos(static_cast<coordinate_t>(black.first), 
                static_cast<coordinate_t>(black.second)) {
    if (white_pos == black_pos) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
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
    if (((white_pos.first == black_pos.first)) || ((white_pos.second == black_pos.second))) {
        return true;
    }
    // Check if on the same diagonal: |Δx| == |Δy|
    // Use int for intermediate calculations to avoid potential issues with std::int8_t
    int delta_x = std::abs(static_cast<int>(white_pos.first) - static_cast<int>(black_pos.first));
    int delta_y = std::abs(static_cast<int>(white_pos.second) - static_cast<int>(black_pos.second));
    if ((delta_x == delta_y)) {
        return true;
    }
    return false;
}

chess_board::operator std::string() const {
    std::stringstream board;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            // Check if current position has white queen
            if (((row == static_cast<int>(white_pos.second)) && (col == static_cast<int>(white_pos.first)))) {
                board << 'W';
            } else { 
                if (((row == static_cast<int>(black_pos.second)) && (col == static_cast<int>(black_pos.first)))) {
                    board << 'B';
                } else {
                    board << '_';
                }
            }
            
            // Add space if not the last column
            if (col < 7) {
                board << ' ';
            }
        }
        // Add newline if not the last row
        if (row < 7) {
            board << '\n';
        }
    }
    return board.str();
}

}  // namespace queen_attack
