#include "queen_attack.h"
#include <stdexcept>
#include <cmath>
#include <string>
#include <utility>
#include <cstdint>

namespace queen_attack {

chess_board::chess_board(const std::string& white, const std::string& black) {
    // Parse white position
    if (white.size() != 2) {
        throw std::domain_error("Invalid white queen position");
    }
    // Use integer codes for comparison to comply with MISRA rules
    const int white_col_code = static_cast<int>(white[0]);
    const int white_row_code = static_cast<int>(white[1]);
    // Check if within valid ranges using integer codes
    if ((white_col_code < static_cast<int>('a')) || 
        (white_col_code > static_cast<int>('h')) || 
        (white_row_code < static_cast<int>('1')) || 
        (white_row_code > static_cast<int>('8'))) {
        throw std::domain_error("Invalid white queen position");
    }
    // Convert to coordinates using integer arithmetic
    white_position.first = static_cast<std::int8_t>(white_col_code - static_cast<int>('a'));
    white_position.second = static_cast<std::int8_t>(white_row_code - static_cast<int>('1'));
    
    // Parse black position
    if (black.size() != 2) {
        throw std::domain_error("Invalid black queen position");
    }
    const int black_col_code = static_cast<int>(black[0]);
    const int black_row_code = static_cast<int>(black[1]);
    if ((black_col_code < static_cast<int>('a')) || 
        (black_col_code > static_cast<int>('h')) || 
        (black_row_code < static_cast<int>('1')) || 
        (black_row_code > static_cast<int>('8'))) {
        throw std::domain_error("Invalid black queen position");
    }
    black_position.first = static_cast<std::int8_t>(black_col_code - static_cast<int>('a'));
    black_position.second = static_cast<std::int8_t>(black_row_code - static_cast<int>('1'));
    
    if ((white_position.first == black_position.first) && 
        (white_position.second == black_position.second)) {
        throw std::domain_error("Queens cannot occupy the same position");
    }
}

std::pair<int, int> chess_board::white() const {
    return std::make_pair(static_cast<int>(white_position.first), 
                          static_cast<int>(white_position.second));
}

std::pair<int, int> chess_board::black() const {
    return std::make_pair(static_cast<int>(black_position.first), 
                          static_cast<int>(black_position.second));
}

bool chess_board::can_attack() const {
    // Check if on the same row or column
    if ((white_position.first == black_position.first) || 
        (white_position.second == black_position.second)) {
        return true;
    }
    // Check if on the same diagonal
    // Cast to int to avoid issues with integer promotion
    const int col_diff = static_cast<int>(white_position.first) - static_cast<int>(black_position.first);
    const int row_diff = static_cast<int>(white_position.second) - static_cast<int>(black_position.second);
    if (std::abs(col_diff) == std::abs(row_diff)) {
        return true;
    }
    return false;
}

}  // namespace queen_attack
